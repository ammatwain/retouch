#ifndef RETOUCH_COMMAND_CORE_HPP
#define RETOUCH_COMMAND_CORE_HPP

#include <filesystem>
#include <iostream>

class CommandCore
{
public:
    CommandCore(std::string aProjectPath = std::filesystem::current_path().string() )
    {
        this->setProjectPaths(aProjectPath);
        this->debug();
    }

    std::string currentDir() {
        return this->path.string();
    }

    void debug()
    {
        std::cout << "this->projectPath()  " << this->projectPath()   << " exists: " << this->projectPathExists()       << std::endl;
        std::cout << "this->retouchPath()  " << this->retouchPath()   << " exists: " << this->retouchPathExists()       << std::endl;
        std::cout << "this->originalPath() " << this->originalPath()  << " exists: " << this->originalPathExists()      << std::endl;
        std::cout << "this->modifiedPath() " << this->modifiedPath()  << " exists: " << this->modifiedPathExists()      << std::endl;
        std::cout << "this->retouchConfig()" << this->retouchConfig() << " exists: " << this->retouchConfigExists()     << std::endl;
    }

    std::string parentCurrentDir() {
        return this->path.parent_path();
    }

protected:
    std::string modifiedPath()
    {
        return this->privateModifiedPath;
    }

    bool modifiedPathExists()
    {
        return std::filesystem::is_directory(this->privateModifiedPath);
    }

    std::string originalPath()
    {
        return this->privateOriginalPath;
    }

    bool originalPathExists()
    {
        return std::filesystem::is_directory(this->privateOriginalPath);
    }

    bool projectExists()
    {
        return  projectPathExists() &&  retouchPathExists() && originalPathExists() && modifiedPathExists() && retouchConfigExists();
    }

    std::string projectPath()
    {
        return this->privateProjectPath;
    }

    bool projectPathExists()
    {
        return std::filesystem::is_directory(this->privateProjectPath);
    }

    bool projectParentPathExists()
    {
        return std::filesystem::is_directory(std::filesystem::path(this->privateProjectPath).parent_path());
    }

    std::string retouchConfig()
    {
        return this->privateRetouchConfig;
    }

    bool retouchConfigExists()
    {
        return std::filesystem::is_regular_file(this->privateRetouchConfig);
    }

    std::string retouchPath()
    {
        return this->privateRetouchPath;
    }

    bool retouchPathExists()
    {
        return std::filesystem::is_directory(this->privateRetouchPath);
    }

    void setProjectPaths(std::string aProjectPath)
    {
        namespace fs = std::filesystem;
        this->privateProjectPath = path.string();
        std::filesystem::path path(aProjectPath);
        if (this->projectParentPathExists()){
            this->privateRetouchPath = path.string() + fs::path::preferred_separator + ".retouch";
            this->privateOriginalPath = this->privateRetouchPath + fs::path::preferred_separator + "original";
            this->privateModifiedPath = this->privateRetouchPath + fs::path::preferred_separator + "modified";
            this->privateRetouchConfig = this->privateModifiedPath + fs::path::preferred_separator + ".retouch.json";
        }
    }

private:
    std::string privateProjectPath;
    std::string privateRetouchPath;
    std::string privateModifiedPath;
    std::string privateOriginalPath;
    std::string privateRetouchConfig;

    inline static const std::filesystem::path path = std::filesystem::current_path();
};


#endif //RETOUCH_COMMAND_CORE_HPP
