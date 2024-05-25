#ifndef RETOUCH_FS_HPP
#define RETOUCH_FS_HPP
#include <iostream>
#include <vector>
#include <filesystem>
#include <string>
#include "retouch_matcher.hpp"

using namespace std::literals;
class RetouchFs
{
public:
    enum flags{
        FOLDERS=1,
        FILES=2,
        ALLENTRIES=3,
        RELATIVE=4,
        RECURSIVE=8,
    };
    std::string getCurrentDir()
    {
        return std::filesystem::current_path().string();
    }
    inline static bool ends_with(std::string const & value, std::string const & ending)
    {
        if (ending.size() > value.size()) return false;
        return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
    }

    inline static bool ends_with(std::string const & value, char const & cending)
    {
        std::string ending = ""; ending += cending;
        if (ending.size() > value.size()) return false;
        return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
    }

    static bool endsWith(std::string_view str, std::string_view suffix)
    {
        return str.size() >= suffix.size() && str.compare(str.size()-suffix.size(), suffix.size(), suffix) == 0;
    }
    static bool endsWith(std::string_view str, char csuffix)
    {
        std::string suffix = ""; suffix += csuffix;
        return str.size() >= suffix.size() && str.compare(str.size()-suffix.size(), suffix.size(), suffix) == 0;
    }

    static bool startsWith(std::string_view str, char cprefix)
    {

        std::string prefix = ""; prefix += cprefix;
        return str.size() >= prefix.size() && str.compare(0, prefix.size(), prefix) == 0;
    }

    static std::vector<std::string> listDirAbsolute(std::string pathString = std::filesystem::current_path().string())
    {
        {
            return RetouchFs::listDir(
                pathString,
                RetouchFs::FOLDERS
            );
        }
    }

    static std::vector<std::string> listDirRelative(std::string pathString = std::filesystem::current_path().string())
    {
        return RetouchFs::listDir(
            pathString,
            RetouchFs::RELATIVE| RetouchFs::FOLDERS
        );
    }

    static std::vector<std::string> listDirAbsoluteRecursive(std::string pathString = std::filesystem::current_path().string())
    {
        return RetouchFs::listDir(
            pathString,
            RetouchFs::RECURSIVE | RetouchFs::FOLDERS
        );
    }

    static std::vector<std::string> listDirRelativeRecursive(std::string pathString = std::filesystem::current_path().string())
    {
        return RetouchFs::listDir(
            pathString,
            RetouchFs::RELATIVE | RetouchFs::RECURSIVE | RetouchFs::FOLDERS
        );
    }

    static std::vector<std::string> listFileAbsolute(std::string pathString = std::filesystem::current_path().string())
    {
        return RetouchFs::listDir(
            pathString,
            RetouchFs::FILES
        );
    }

    static std::vector<std::string> listFileRelative(std::string pathString = std::filesystem::current_path().string())
    {
        return RetouchFs::listDir(
            pathString,
            RetouchFs::RELATIVE | RetouchFs::FILES
        );
    }

    static std::vector<std::string> listFileAbsoluteRecursive(std::string pathString = std::filesystem::current_path().string())
    {
        return RetouchFs::listDir(
            pathString,
            RetouchFs::RECURSIVE | RetouchFs::FILES
        );
    }

    static std::vector<std::string> listFileRelativeRecursive(std::string pathString = std::filesystem::current_path().string())
    {
        return RetouchFs::listDir(
            pathString,
            RetouchFs::RELATIVE | RetouchFs::RECURSIVE | RetouchFs::FILES
        );
    }

    static std::vector<std::string> listAllAbsolute(std::string pathString = std::filesystem::current_path().string())
    {
        return RetouchFs::listDir(
            pathString,
            RetouchFs::ALLENTRIES
        );
    }

    static std::vector<std::string> listAllRelative(std::string pathString = std::filesystem::current_path().string())
    {
        return RetouchFs::listDir(
            pathString,
            RetouchFs::RELATIVE | RetouchFs::ALLENTRIES
        );
    }

    static std::vector<std::string> listAllAbsoluteRecursive(std::string pathString = std::filesystem::current_path().string())
    {
        return RetouchFs::listDir(
            pathString,
            RetouchFs::RECURSIVE | RetouchFs::ALLENTRIES
        );
    }

    static std::vector<std::string> listAllRelativeRecursive(std::string pathString = std::filesystem::current_path().string())
    {
        return RetouchFs::listDir(
            pathString,
            RetouchFs::RELATIVE | RetouchFs::RECURSIVE | RetouchFs::ALLENTRIES
        );
    }

    static std::vector<std::string> listDir(std::string pathString, unsigned int aFlags ){
        bool relative = aFlags & RetouchFs::RECURSIVE;
        bool recursive = aFlags & RetouchFs::RECURSIVE;
        bool acceptFiles = aFlags & RetouchFs::FILES;
        bool acceptFolders = aFlags & RetouchFs::FOLDERS;
        Matcher matcher("*[!.cmake]");
        matcher
            .addPattern("*[!.cpp]")
            .addPattern("*[!.yaml]")
            .addPattern("*[!.out]");
        if (!(acceptFiles&&acceptFolders)) {
            acceptFiles = true;
            acceptFolders = true;
        }
        namespace fs = std::filesystem;
        std::vector<std::string> list;
        if (!RetouchFs::endsWith(pathString,fs::path::preferred_separator)){
            pathString += fs::path::preferred_separator;
        }

        fs::path path(pathString);

        // Iterate over the std::filesystem::directory_entry elements using `auto`
        if (recursive) {
            for (auto const& dir_entry : fs::recursive_directory_iterator(path)) {
                if (dir_entry.is_regular_file() && acceptFiles)
                {
                    if (matcher.match(dir_entry.path().filename().string())) {
                        list.push_back(fs::absolute(dir_entry).string());
                    }
                }
                else if (dir_entry.is_directory() && acceptFolders) {
                    list.push_back(fs::absolute(dir_entry).string()+fs::path::preferred_separator);
                }
            }
        } else {
            for (auto const& dir_entry : fs::directory_iterator(path)) {
                if (dir_entry.is_regular_file() && acceptFiles)
                {
                    if (matcher.match(dir_entry.path().filename().string())) {
                        list.push_back(fs::absolute(dir_entry).string());
                    }
                }
                else if (dir_entry.is_directory() && acceptFolders) {
                    list.push_back(fs::absolute(dir_entry).string()+fs::path::preferred_separator);
                }
            }
        }
        if (relative){
            int strLen = pathString.size();
            for(int i = 0 ; i < list.size(); i++){
                if (list[i].find(pathString)==0) {
                    list[i].replace(0,strLen,"");
                }
            }
        }

        for(int i = 0 ; i < list.size(); i++){
            std::cout << list[i] << std::endl;
        }
        return list;

    }

};

#endif //RETOUCH_FS_HPP
