#include "src/retouch_console_escape.hpp"
#include "src/retouch_console_cursor.hpp"

#include "src/retouch_project.hpp"
#include "src/retouch_options.hpp"
#include "src/retouch_fs.hpp"

int main(int argc, const char* argv[])
{
    Retouch::Project project("../../te12313ts//");
    return 0;

    std::vector<std::string> bootstrap_errors;
    std::vector<std::string> externals = {
        "ln    ",
        "cp    ",
        "rm    ",
        "mv    ",
        "ctags ",
        "mkdir ",
        "wget  ",
        "curl  ",
        "git   ",
    };
    for (int i = 0 ; i < externals.size() ; i++) {
        std::string command = externals[i] + "--version 1>/dev/null 2>/dev/null"; 
        if (!(system(command.c_str())==0)) {
            std::string error = "";
            error += Esc::bgRed;
            error += Esc::fgYellow;
            error += Esc::bright;
            error += " ";
            error += externals[i];
            error += Esc::normalColorOrIntensity;
            error += "non è installato oppure non è disponibile nel path di ricerca ";
            error += Esc::reset;
            bootstrap_errors.push_back(error);
        }

    }
   
    if (bootstrap_errors.size())
    {
        for (int i = 0; i < bootstrap_errors.size() ; i++) {
            std::cerr << " " << bootstrap_errors[i] << " " << std::endl;
        }
        return 1;
    }
    Retouch::Fs::listAllRelativeRecursive("",
        {
            ".*\\.txt$",
            ".*\\.idx$",
        }
    );

    Retouch::Options retouchOptions(argc, argv);
/*
    if (!parseCommand(argc, argv))
    {
        return 1;
    }
*/


    std::pair<int,int> pos = Retouch::Console::Cursor::pos();
    int col = pos.first;
    int row = pos.second;
    if (row != -1 && col != -1) {
        Retouch::Console::Cursor::goUp(8);
        Retouch::Console::Cursor::goForward(30);
        Retouch::Console::Cursor::eraseInDisplay(3);
        std::cout << "position 1: x = " << col << " ; y = " << row << std::endl;
        Retouch::Console::Cursor::goDown(8);
        Retouch::Console::Cursor::goBack(10);
        std::cout << "position 2: x = " << col << " ; y = " << row << std::endl;
    } else {
        std::cerr << "Failed to get cursor position" << std::endl;
    }
    return 0;
}
