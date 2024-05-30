#ifndef RETOUCH_PROJECT_HPP
#define RETOUCH_PROJECT_HPP

#include <string>
#include <filesystem>

namespace fs = std::filesystem;

namespace Retouch
{

class Project
{
public:
    Project(std::string aWorkDir, std::string aRetouchDir = "")
    {
        fs::path workPath = fs::absolute(aWorkDir);

        if (fs::is_directory(workPath.parent_path())) {
            // la cosa è fattibile, andiamo avanti
            if (!fs::is_directory(workPath)) {
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
    fs::path privWorkPath;

}

} // namespace Retouch;

#endif // RETOUCH_PROJECT_HPP
