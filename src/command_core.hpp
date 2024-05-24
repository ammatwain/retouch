#ifndef RETOUCH_COMMAND_CORE_HPP
#define RETOUCH_COMMAND_CORE_HPP

#include <filesystem>
#include <iostream>
#include <map>
#include "extern/cxxopts/cxxopts.hpp"
#include "colorize.hpp"

class CommandCore
{
public:

    CommandCore(int argc, const char* argv[])
    {
        this->privateArgc = argc;
        this->privateArgv = argv;
        this->protectedArgc = this->privateArgc;
        this->protectedArgv = this->privateArgv;
        this->privateDefaultArgs[0] = this->privateArgv[0];
        this->setOptions();
    }

    CommandCore(std::string aCommandName, CommandCore* aParent)
    {
        this->privateParent = aParent;
        if (aCommandName==""){
            aCommandName = this->defaultCommand();
        }
        this->privateName = aCommandName;
        this->root()->addChild(aCommandName, this);
        this->setOptions();
    }

    ~CommandCore()
    {
        delete this->privateOptions;
    }

    int argc()
    {
        if (!this->isRoot()) {
            return this->root()->argc() - 1;
        } else {
            return this->protectedArgc;
        }
    }

    std::string argv(int aIndex)
    {
        if (aIndex>=0 && aIndex<this->argc())
        {
            return this->argv()[aIndex];
        }
        return "";
    }

    const char** argv()
    {
        if (!this->isRoot()) {
            return &this->root()->argv()[1];
        }
        return this->protectedArgv;
    }

    std::string command()
    {
        //return this->privateName;
        if (!this->isRoot()){
            return this->privateName; //argv(0);
        }
        return "";
    }

    const char* defaultCommand()
    {
        return this->privateDefaultArgs[1];;
    }

    bool isRoot()
    {
        return this->parent() == nullptr;
    }

    cxxopts::Options* options()
    {
        return this->privateOptions;
    }

    CommandCore* parent()
    {
        return this->privateParent;
    }

    virtual int parse() {
        std::string commandString = this->privateDefaultArgs[1];
        CommandCore* command = nullptr;
        if (this->privateArgc>1){
            std::string  tmpCommandString = this->privateArgv[1];
            auto it = this->privateChildMap.find(tmpCommandString);
            if (it != this->privateChildMap.end()) {
                // if key is found
                command = it->second;
                return command->parse();
            }
        }
        this->protectedArgc++;
        this->protectedArgv = new const char*[this->protectedArgc];
        this->protectedArgv[0] = this->privateDefaultArgs[0];
        this->protectedArgv[1] = this->privateDefaultArgs[1];

        if (this->protectedArgc>2){
            for(int i = 2; i< this->protectedArgc; i++) {
                this->protectedArgv[i] = this->privateArgv[i-1];
            }
        }
        auto it = this->privateChildMap.find(commandString);
        if (it != this->privateChildMap.end()) {
            // if key is found
            command = it->second;
            return command->parse();
        }
        std::cout << "Map does not contain key '" << this->protectedArgv[1] << "'" << std::endl;
        return 1;
    };

    cxxopts::ParseResult parseOptions(){
        return this->options()->parse(this->argc(), this->argv());
    }

    std::string program()
    {
        std::string firstParam = this->root()->argv(0);
        return firstParam.substr(firstParam.find_last_of("/\\") + 1);
    }

    CommandCore* root()
    {
        if (this->parent()!=nullptr){
            return this->parent()->root();
        } else {
            return this;
        }
    }

    void setOptions()
    {
        std::string cmdline = "";
        if (this->command()!=this->defaultCommand()) {
            cmdline = Esc::bold + this->program() + " " + this->command() + Esc::reset;
        } else {
            cmdline = Esc::bold + this->program() + Esc::reset;
        }
        this->privateOptions = new cxxopts::Options(cmdline , cmdline);
        this->privateOptions->positional_help("[optional args]").show_positional_help();
        this->privateOptions
            ->set_width(70)
            .set_tab_expansion()
            .allow_unrecognised_options()
            .add_options()
            ("h,help","(Print this help)")
            ;
    }

    std::string currentDir() {
        return this->currentPath().string();
    }

    std::filesystem::path currentPath() {
        return std::filesystem::current_path();
    }

    void debug()
    {
        std::cout << "this->projectPath()  " << this->projectDir()   << " exists: " << this->projectDirExists()       << std::endl;
        std::cout << "this->retouchPath()  " << this->retouchDir()   << " exists: " << this->retouchDirExists()       << std::endl;
        std::cout << "this->originalPath() " << this->originalDir()  << " exists: " << this->originalDirExists()      << std::endl;
        std::cout << "this->modifiedPath() " << this->modifiedDir()  << " exists: " << this->modifiedDirExists()      << std::endl;
        std::cout << "this->retouchConfig()" << this->retouchConfigFile() << " exists: " << this->retouchConfigFileExists()     << std::endl;
    }

    std::string parentCurrentDir() {
        return this->currentPath().parent_path();
    }

protected:
    void addChild(std::string aCommandName, CommandCore* aChildCommand)
    {
        //this->privateChildMap[aCommandName] = aChildCommand;
        this->privateChildMap.insert({aCommandName,aChildCommand});
    }

    std::string modifiedDir()
    {
        return this->privateModifiedDir;
    }

    bool modifiedDirExists()
    {
        return std::filesystem::is_directory(this->privateModifiedDir);
    }

    std::string originalDir()
    {
        return this->privateOriginalDir;
    }

    bool originalDirExists()
    {
        return std::filesystem::is_directory(this->privateOriginalDir);
    }

    bool projectExists()
    {
        return  projectDirExists() &&  retouchDirExists() && originalDirExists() && modifiedDirExists() && retouchConfigFileExists();
    }

    std::string projectDir()
    {
        return this->privateProjectDir;
    }

    bool projectDirExists()
    {
        return std::filesystem::is_directory(this->privateProjectDir);
    }

    bool projectParentDirExists()
    {
        return std::filesystem::is_directory(std::filesystem::path(this->privateProjectDir).parent_path());
    }

    std::string retouchConfigFile()
    {
        return this->privateRetouchConfigFile;
    }

    bool retouchConfigFileExists()
    {
        return std::filesystem::is_regular_file(this->privateRetouchConfigFile);
    }

    std::string retouchDir()
    {
        return this->privateRetouchDir;
    }

    bool retouchDirExists()
    {
        return std::filesystem::is_directory(this->privateRetouchDir);
    }

    void setProjectDirs(std::string aProjectDir)
    {
        namespace fs = std::filesystem;
        //this->privateProjectDir = path.string();
        std::filesystem::path path(aProjectDir);
        if (this->projectParentDirExists()){
            this->privateRetouchDir = path.string() + fs::path::preferred_separator + ".retouch";
            this->privateOriginalDir = this->privateRetouchDir + fs::path::preferred_separator + "original";
            this->privateModifiedDir = this->privateRetouchDir + fs::path::preferred_separator + "modified";
            this->privateRetouchConfigFile = this->privateModifiedDir + fs::path::preferred_separator + ".retouch.json";
        }
    }
protected:
    int protectedArgc = 0;
    const char** protectedArgv;

private:
    int privateArgc;
    const char** privateArgv;
    const char* privateDefaultArgs[2] = {"","default"};
    std::string privateName = "";
private:
    std::string privateProjectDir;
    std::string privateRetouchDir;
    std::string privateModifiedDir;
    std::string privateOriginalDir;
    std::string privateRetouchConfigFile;

private:
    std::map<std::string,CommandCore*> privateChildMap;
    CommandCore* privateParent = nullptr;
    cxxopts::Options* privateOptions;
};


#endif //RETOUCH_COMMAND_CORE_HPP
