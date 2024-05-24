#ifndef RETOUCH_COMMAND_CORE_HPP
#define RETOUCH_COMMAND_CORE_HPP

#include <filesystem>
#include <iostream>
#include <map>
#include "extern/cxxopts/cxxopts.hpp"

class CommandCore
{
public:

    CommandCore(int argc, const char* argv[])
    {
        this->privateArgc = argc;
        this->privateArgv = argv;
        this->privateOptions = new cxxopts::Options(this->program(), "");

        //this->setProjectDirs(aProjectPath);
        /*
        std::string command = this->basename(argv[0]);
        std::string program_command = Esc::bold +  program + " " + command + Esc::reset;
        try
        {
            std::unique_ptr<cxxopts::Options> allocated(new cxxopts::Options(program_command, program_command));
            cxxopts::Options& options = *allocated;
            options.positional_help("[optional args]").show_positional_help();
            options
                .set_width(70)
                .set_tab_expansion()

        this->debug();
        */
    }

    CommandCore(std::string aCommandName, CommandCore* aParent)
    {
        this->privateParent = aParent;
        this->root()->addChild(aCommandName, this);
        this->privateOptions = new cxxopts::Options(this->program(), this->command());
    }

    ~CommandCore()
    {
        delete this->privateOptions;
    }

    int argc()
    {
        if (this->isRoot()) {
            return this->privateArgc;
        } else {
            return this->privateArgc - 1;
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
            return this->privateArgv++;
        }
        return this->privateArgv;
    }

    std::string command()
    {
        if (!isRoot()){
            return this->argv(0);
        }
        return "";
    }

    bool isRoot()
    {
        return this->parent() == nullptr;
    }

    CommandCore* parent()
    {
        return this->privateParent;
    }

    void parse() {
        std::string commandString = this->argv(1);
        if (commandString=="") {
            commandString = "default";
        }
        auto it = this->privateChildMap.find(commandString);

        if (it != this->privateChildMap.end()) {
            // if key is found
            //std::cout << "Map contains key '" << commandString  << "' with value: " << it->second << std::endl;
            it->second->parse();
        }
        else {
            // if key is not found
            std::cout << "Map does not contain key '" << commandString << "'" << std::endl;
        }

        //if (this->privateChildMap.)
        //CommandCore* command = this->privateChildMap[""]
        /*
        if (command=="")
        {
            return parseCommandDefault(argc, argv);
        }
        else if (command=="init")
        {
            return parseCommandInit(argc, argv);
        }
        else
        {
            return parseCommandUnknown(argc, argv);
        }
        return true;
        */
    };

    cxxopts::ParseResult parseOptions(){
        return this->privateOptions->parse(this->argc(), this->argv());
    }

    std::string program()
    {
        std::string firstParam = this->root()->argv(0);
        return firstParam.substr(firstParam.find_last_of("/\\") + 1);
    }

    CommandCore* root()
    {
        if (this->parent()){
            return this->parent()->root();
        } else {
            return this;
        }
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
        this->privateChildMap[aCommandName] = aChildCommand;
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

private:
    int privateArgc;
    const char** privateArgv;
    std::string privateName = "";
private:
    std::string privateProjectDir;
    std::string privateRetouchDir;
    std::string privateModifiedDir;
    std::string privateOriginalDir;
    std::string privateRetouchConfigFile;

private:
    std::map<std::string,CommandCore*> privateChildMap;
    CommandCore* privateParent;
    cxxopts::Options* privateOptions;
};


#endif //RETOUCH_COMMAND_CORE_HPP
