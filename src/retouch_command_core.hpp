#ifndef RETOUCH_COMMAND_CORE_HPP
#define RETOUCH_COMMAND_CORE_HPP

#include <filesystem>
#include <iostream>
#include <map>
#include "extern/cxxopts/cxxopts.hpp"
#include "retouch_utils.hpp"
#include "retouch_console_escape.hpp"


namespace Esc = Retouch::Console::Escape;

namespace Retouch{

namespace Command{

class Core
{
public:

    Core(int argc, const char* argv[])
    {
        this->privateArgc = argc;
        this->privateArgv = argv;
        this->protectedArgc = this->privateArgc;
        this->protectedArgv = this->privateArgv;
        this->privateDefaultArgs[0] = this->privateArgv[0];
        this->setOptions();
    }

    Core(std::string aCommandName, Core* aParent)
    {
        this->privateParent = aParent;
        if (aCommandName==""){
            aCommandName = this->defaultCommand();
        }
        this->privateName = aCommandName;
        this->root()->addChild(aCommandName, this);
        this->setOptions();
    }

    ~Core()
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

    Core* parent()
    {
        return this->privateParent;
    }

    virtual int parse() {
        int errorCode = 0;
        std::string commandString = this->privateDefaultArgs[1];
        Core* command = nullptr;
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

        cxxopts::ParseResult result = this->parseOptions();
        if (result.count("work-dir"))
        {
            std::cout << "work-dir " << result.count("work-dir") << std::endl;
            errorCode = this->setProjectDirs(result["work-dir"].as<std::string>());
        } else {
            errorCode = this->setProjectDirs();
        }

        if (errorCode) {
            return errorCode;
        }

        std::cout << "this->workDir()" << this->workDir() << std::endl;

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
        cxxopts::ParseResult result = this->options()->parse(this->argc(), this->argv());
        if (result.count("help"))
        {
            std::cout << this->options()->help({"", "Group"}) << std::endl;
            return 0;
        }
        if (result.unmatched().size()) {
            std::cout << std::endl << Esc::bgRed << Esc::bright << Esc::fgYellow << " ERROR!!! " << result.unmatched().size() << " unmatched options: ";
            for (const auto& option: result.unmatched())
            {
                std::cout << "'" << option << "' ";
            }
            std::cout << Esc::reset << std::endl << std::endl;
            std::cout << this->options()->help({"", "Group"}) << std::endl;
            return 1;
        }

    }

    std::string program()
    {
        std::string firstParam = this->root()->argv(0);
        return firstParam.substr(firstParam.find_last_of("/\\") + 1);
    }

    Core* root()
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
            ->set_width(80)
            .set_tab_expansion()
            .allow_unrecognised_options()
            .add_options()
            ("h,help","(Print this help)")
            ("W,work-dir","(Set the work dir, usually <work-dir>/<retouch-dir>)",cxxopts::value<std::string>())
            ("R,retouch-dir","(Set the .retouch dir, usually <work-dir>/<retouch-dir>)",cxxopts::value<std::string>())
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
        std::cout << "this->WorkDir()           " << this->workDir()   << " exists: " << this->workDirExists()       << std::endl;
        std::cout << "this->retouchDir()        " << this->retouchDir()   << " exists: " << this->retouchDirExists()       << std::endl;
        std::cout << "this->originalDir()       " << this->originalDir()  << " exists: " << this->originalDirExists()      << std::endl;
        std::cout << "this->modifiedDir()       " << this->modifiedDir()  << " exists: " << this->modifiedDirExists()      << std::endl;
        std::cout << "this->retouchConfigFile() " << this->retouchConfigFile() << " exists: " << this->retouchConfigFileExists()     << std::endl;
    }

    std::string parentCurrentDir() {
        return this->currentPath().parent_path();
    }

protected:
    void addChild(std::string aCommandName, Core* aChildCommand)
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
        return  workDirExists() &&  retouchDirExists() && originalDirExists() && modifiedDirExists() && retouchConfigFileExists();
    }

    std::string workDir()
    {
        return this->privateWorkDir;
    }

    bool workDirExists()
    {
        return std::filesystem::is_directory(this->privateWorkDir);
    }

    bool parentWorkDirExists()
    {
        return std::filesystem::is_directory(std::filesystem::path(this->privateWorkDir).parent_path());
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

    int setProjectDirs(std::string aWorkDir = std::filesystem::current_path().string())
    {
        int errorCode = 0;
        namespace fs = std::filesystem;
        //
        while(endsWith(aWorkDir, Retouch::DIRSEP)) {
            aWorkDir.resize(aWorkDir.size()-1);
        }
        //
        std::filesystem::path aWorkDirPath(aWorkDir);
        //
        this->privateWorkDir = std::filesystem::weakly_canonical(aWorkDirPath).string();
        //
        if (this->parentWorkDirExists()){
            this->privateRetouchDir = this->privateWorkDir + fs::path::preferred_separator + ".retouch";
            this->privateOriginalDir = this->privateRetouchDir + fs::path::preferred_separator + "original";
            this->privateModifiedDir = this->privateRetouchDir + fs::path::preferred_separator + "modified";
            this->privateRetouchConfigFile = this->privateModifiedDir + fs::path::preferred_separator + ".retouch.json";
        } else {
            errorCode = 1 ;
            std::cerr
                << Esc::bgRed
                << Esc::fgYellow
                << Esc::bold
                << " EXIT ERRORE!!! LA PARENT-DIRECTORY DELLA WORK-DIRECTORY DEVE ESSERE UN PERCORSO ESISTENTE! "
                << Esc::reset << std::endl;
            //throw std::runtime_error("ERRORE!!! ALMENO IL PARENT DI WORKDIR DEVE ESISTERE");
        }
        //
        return errorCode;
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
    std::string privateWorkDir;
    std::string privateRetouchDir;
    std::string privateModifiedDir;
    std::string privateOriginalDir;
    std::string privateRetouchConfigFile;

private:
    std::map<std::string,Core*> privateChildMap;
    Core* privateParent = nullptr;
    cxxopts::Options* privateOptions;
};

} //namespace Retouch::Command

} //namespace Retouch

#endif //RETOUCH_COMMAND_CORE_HPP
