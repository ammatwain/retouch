#ifndef RETOUCH_FS_HPP
#define RETOUCH_FS_HPP
#include <iostream>
#include <vector>
#include <filesystem>
#include <string>

#include "retouch_matcher.hpp"
#include "retouch_utils.hpp"

using namespace std::literals;
namespace fs = std::filesystem;

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

    static std::vector<std::string> listDirAbsolute(std::string pathString = "", std::vector<std::string> ignored = {})
    {
        {
            return RetouchFs::listDir(
                pathString,
                RetouchFs::FOLDERS,
                ignored
            );
        }
    }

    static std::vector<std::string> listDirRelative(std::string pathString = "", std::vector<std::string> ignored = {})
    {
        return RetouchFs::listDir(
            pathString,
            RetouchFs::RELATIVE| RetouchFs::FOLDERS,
            ignored
        );
    }

    static std::vector<std::string> listDirAbsoluteRecursive(std::string pathString = "", std::vector<std::string> ignored = {})
    {
        return RetouchFs::listDir(
            pathString,
            RetouchFs::RECURSIVE | RetouchFs::FOLDERS,
            ignored
        );
    }

    static std::vector<std::string> listDirRelativeRecursive(std::string pathString = "", std::vector<std::string> ignored = {})
    {
        return RetouchFs::listDir(
            pathString,
            RetouchFs::RELATIVE | RetouchFs::RECURSIVE | RetouchFs::FOLDERS,
            ignored
        );
    }

    static std::vector<std::string> listFileAbsolute(std::string pathString = "", std::vector<std::string> ignored = {})
    {
        return RetouchFs::listDir(
            pathString,
            RetouchFs::FILES,
            ignored
        );
    }

    static std::vector<std::string> listFileRelative(std::string pathString = "", std::vector<std::string> ignored = {})
    {
        return RetouchFs::listDir(
            pathString,
            RetouchFs::RELATIVE | RetouchFs::FILES,
            ignored
        );
    }

    static std::vector<std::string> listFileAbsoluteRecursive(std::string pathString = "", std::vector<std::string> ignored = {})
    {
        return RetouchFs::listDir(
            pathString,
            RetouchFs::RECURSIVE | RetouchFs::FILES,
            ignored
        );
    }

    static std::vector<std::string> listFileRelativeRecursive(std::string pathString = "", std::vector<std::string> ignored = {})
    {
        return RetouchFs::listDir(
            pathString,
            RetouchFs::RELATIVE | RetouchFs::RECURSIVE | RetouchFs::FILES
        );
    }

    static std::vector<std::string> listAllAbsolute(std::string pathString = "", std::vector<std::string> ignored = {})
    {
        return RetouchFs::listDir(
            pathString,
            RetouchFs::ALLENTRIES,
            ignored
        );
    }

    static std::vector<std::string> listAllRelative(std::string pathString = "", std::vector<std::string> ignored = {})
    {
        return RetouchFs::listDir(
            pathString,
            RetouchFs::RELATIVE | RetouchFs::ALLENTRIES,
            ignored
        );
    }

    static std::vector<std::string> listAllAbsoluteRecursive(std::string pathString = "", std::vector<std::string> ignored = {})
    {
        return RetouchFs::listDir(
            pathString,
            RetouchFs::RECURSIVE | RetouchFs::ALLENTRIES,
            ignored
        );
    }

    static std::vector<std::string> listAllRelativeRecursive(std::string pathString = "", std::vector<std::string> ignored = {})
    {
        return RetouchFs::listDir(
            pathString,
            RetouchFs::RELATIVE | RetouchFs::RECURSIVE | RetouchFs::ALLENTRIES,
            ignored
        );
    }

    static std::vector<fs::directory_entry> ls(std::string pathString, bool recursive) {
        std::vector<fs::directory_entry> vec;
        if (recursive) {
            for (auto const& dir_entry : fs::recursive_directory_iterator(pathString)) {
                vec.push_back(dir_entry);
            }
        } else {
            for (auto const& dir_entry : fs::directory_iterator(pathString)) {
                vec.push_back(dir_entry);
            }
        }
        return vec;
    }

    static std::vector<std::string> listDir(std::string pathString, unsigned int aFlags, std::vector<std::string> ignored = {}){
        Matcher* matcher = nullptr;
        if (pathString=="" || pathString == "." || pathString == "./")  pathString = std::filesystem::current_path().string();
        if (!((aFlags & RetouchFs::FILES) || (aFlags & RetouchFs::FOLDERS))) {
            aFlags = aFlags | RetouchFs::FILES | RetouchFs::FOLDERS;
        }
        if (!Retouch::endsWith(pathString,fs::path::preferred_separator)){
            pathString += fs::path::preferred_separator;
        }
        int pathStringLen = pathString.size();
        if (ignored.size()){
            matcher = new Matcher();
            for(int i = 0 ; i < ignored.size() ; i++) {
                matcher->addPattern(ignored[i]);
            }
        }
        /*
        matcher->addPattern("^(?!\\.git).*$");
        matcher->addPattern("^(?!\\.git\\/).*$");
        matcher->addPattern("^(?!\\.retouch\\/).*$");
        matcher->addPattern("^(?!build\\/).*$");
        matcher->addPattern("^(?!builds\\/).*$");
        matcher->addPattern("^(?!buildscripts\\/).*$");
        matcher->addPattern("^(?!share\\/).*$");
        matcher->addPattern("^(?!src\\/).*$");
        matcher->addPattern("^(?!thirdparty\\/).*$");
        matcher->addPattern("^(?!tools\\/).*$");
        matcher->addPattern("^(?!test\\/).*$");
        matcher->addPattern("^(?!vtest\\/).*$");
        */
        std::vector<std::string> list;

        std::string absoluteEntryName = "";
        std::string relativeEntryName = "";
        std::vector<fs::directory_entry> ils = RetouchFs::ls(pathString, aFlags & RetouchFs::RECURSIVE);
        for (int i = 0 ; i < ils.size() ; i++){
            fs::directory_entry &dir_entry = ils[i];
            std:: string absoluteEntryName = fs::absolute(dir_entry).string();
            if (dir_entry. is_directory()) absoluteEntryName += fs::path::preferred_separator;
            std:: string relativeEntryName = absoluteEntryName;
            if (relativeEntryName.find(pathString)==0) relativeEntryName.replace(0, pathStringLen, "");
            if ( (dir_entry.is_regular_file() && aFlags & RetouchFs::FILES) || (dir_entry.is_directory() && aFlags & RetouchFs::FOLDERS) )
            {
                bool ok = (matcher==nullptr) || !matcher->match(relativeEntryName);
                if (ok) {
                    if (aFlags & RetouchFs::RELATIVE){
                        list.push_back(relativeEntryName);
                    } else {
                        list.push_back(absoluteEntryName);
                    }
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
