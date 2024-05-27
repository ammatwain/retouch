/*

Copyright (c) 2014 Jarryd Beck

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/
#include "src/options.hpp"
#include "src/colorize.hpp"
#include "src/retouch_fs.hpp"

int main(int argc, const char* argv[])
{
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
    RetouchFs::listAllRelativeRecursive("",
        {
            ".*\\.txt$",
            ".*\\.idx$",
        }
    );

    RetouchOptions retouchOptions(argc, argv);
/*
    if (!parseCommand(argc, argv))
    {
        return 1;
    }
*/
  return 0;
}
