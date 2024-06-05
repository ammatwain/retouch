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
    Project(std::string aWorkDir="", bool forceProjectNameCreation = false )
    {
        /**
         * togliamo gli eventuali DIRSEP dalla fine del PATH
         */
        while (Retouch::endsWith(aWorkDir,Retouch::DIRSEP)){
            aWorkDir.pop_back();
        }

        try {
            this->privWeaklyCanonicalWorkPath = fs::weakly_canonical(fs::absolute(aWorkDir));
        } catch (const std::filesystem::filesystem_error &e) {
            std::cerr << "GENERAL ERROR WITH THE PROJECT PATH" << std::endl;
        }

        try {
            this->privParentWorkPath = fs::canonical(this->privWeaklyCanonicalWorkPath.parent_path());
        } catch (const std::filesystem::filesystem_error &e) {
            std::cerr << "ERROR: You're trying to build a project in a path where the parent directory doesn't exist." << std::endl;
        }

        this->privProjectName = this->privWeaklyCanonicalWorkPath.filename().string();

        try {
            this->privWorkPath = fs::canonical(this->privWeaklyCanonicalWorkPath);
        } catch (const std::filesystem::filesystem_error &e1) {
            if (forceProjectNameCreation) {
                if (this->isValidProjectName(this->privProjectName)) {
                    std::filesystem::create_directory(this->privWeaklyCanonicalWorkPath);
                } else {
                    std::cerr << "ERROR! The project name contains characters outside the allowed range [A-Za-z0-9._-]" << std::endl;
                }
            }
            try {
                this->privWorkPath = fs::canonical(this->privWeaklyCanonicalWorkPath);
            } catch (const std::filesystem::filesystem_error &e2) {
                std::cerr << "WARNING! The path does not exist and the user did not request its creation." << std::endl;
            }
        }
        std::cout << this->privWorkPath << std::endl;

/*
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
*/
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

    /**
     * @brief privWeaklyCanonicalWorkPath
     * il path come viene richiesto,
     * potrebbe contenere degli errori,
     * per adesso lo prendiamo così com'è.
     */
    fs::path privWeaklyCanonicalWorkPath;

    /**
     * @brief privParentWorkPath
     * il parent path della cartella
     * impostata come progetto.
     * questo DEVE esistere
     */
    fs::path privParentWorkPath;

    /**
     * @brief privWorkPath
     * il path vero e proprio,
     * basato su parentWorkPath + DIRSEP + projectName;
    */
    fs::path privWorkPath;
    /**
     * @brief privProjectName
     * il nome del progetto.
     * è l'ultima stringa del path.
     */
    std::string privProjectName;
    const std::string privPosixPortableCharSet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789._-";
};

} // namespace Retouch;

#endif // RETOUCH_PROJECT_HPP
