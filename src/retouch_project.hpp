#ifndef RETOUCH_PROJECT_HPP
#define RETOUCH_PROJECT_HPP

#include <iostream>
#include <string>
#include <filesystem>
#include "retouch_utils.hpp"

namespace fs = std::filesystem;

namespace Retouch
{

class Project
{
public:
    Project(std::string aWorkDir="")
    {
        while (Retouch::endsWith(aWorkDir,Retouch::DIRSEP)){
            aWorkDir.pop_back();
        }
        /*
        if (aWorkDir.rfind(Retouch::DIRSEP ,0)==0) {
            std::cout << "path absolute" << std::endl;
        } else {
            if (aWorkDir.rfind("." + Retouch::DIRSEP ,0)==0) {
                aWorkDir.erase(0,2);
            }
            std::cout << Retouch::DIRSEP << std::endl;
            aWorkDir = fs::current_path().generic_string() + Retouch::DIRSEP + aWorkDir;
        }
        */
        std::cout << "aWorkDir "  << aWorkDir << std::endl;
        fs::path weaklyCanonicalWorkPath;
        fs::path parentPath;
        fs::path workPath;
        std::string projectName;
        //aWorkDir = fs::absolute(fs::current_path()).string();
        try {
            weaklyCanonicalWorkPath = fs::weakly_canonical(fs::absolute(aWorkDir));
        } catch (const std::filesystem::filesystem_error &e) {
            std::cout << "ERRORE GENERICO SUL PATH DEL PROGETTO" << std::endl;
        }
        std::cout << "weaklyCanonicalWorkPath " << weaklyCanonicalWorkPath << std::endl;

        try {
            parentPath = fs::canonical(weaklyCanonicalWorkPath.parent_path());
        } catch (const std::filesystem::filesystem_error &e) {
            std::cout << "ERRORE 2" << std::endl;
        }
        std::cout << "parentPath " << parentPath << std::endl;
        projectName = weaklyCanonicalWorkPath.filename().string();

        try {
            workPath = fs::canonical(weaklyCanonicalWorkPath);
        } catch (const std::filesystem::filesystem_error &e1) {
            if (this->isValidProjectName(projectName)) {
                std::filesystem::create_directory(weaklyCanonicalWorkPath);
            }
            try {
                workPath = fs::canonical(weaklyCanonicalWorkPath);
            } catch (const std::filesystem::filesystem_error &e2) {
                std::cout << "ERRORE 3" << std::endl;
            }
        }
        std::cout << workPath << std::endl;


        if (fs::is_directory(workPath.parent_path())) {
            std::cout << "LA CARTELLA PARENT ESISTE" << std::endl;
            // la cosa è fattibile, andiamo avanti
            if (!fs::is_directory(workPath)) {
                std::cout << "LA CARTELLA NON ESISTE" << workPath.filename() << std::endl;
                // il folder del progetto NON esiste.
                // verifichiamo sia fattibile tentando un mkdir
                // altrimenti mandiamo tutto a monte
            }
            // a questo punto work dir dovrebbe esistere
            // ed essere congrutente.
            if (fs::is_directory(workPath)) {
                // il folder del progetto esiste quindi
                // verifichiamo che dentro sia tutto a posto
                this->privWorkPath = workPath;
            } else {
            }
        } else {
            // il parentpath della workdir non esiste,
            // stiamo cercando di realizzare progetto su un qualcosa
            // le cui fondamenta non hanno fondamenta.
            // Urge evocare un nulla di fatto,
            // la cosa è non è assolutamente realistica,
            // solleviamo una eccezione,
            // mandiamo tutto a monte,
            // usciamo dal programma
            throw std::runtime_error("ERROR: You're trying to build a project in a path where the parent directory doesn't exist.");
        }
    }
private:
    bool isValidProjectName(std::string aProjectName) {
        for(int i = 0 ; i < aProjectName.size() ; i++) {
            auto c = aProjectName[i];
            if (this->privPosixPortableCharSet.find(aProjectName[i])== std::string::npos) {
                return false;
            }
        }
        return true;
    }
    fs::path privWorkPath;
    const std::string privPosixPortableCharSet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789._-";
};

} // namespace Retouch;

#endif // RETOUCH_PROJECT_HPP
