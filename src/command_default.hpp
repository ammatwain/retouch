#ifndef RETOUCH_COMMAND_DEFAULT_HPP
#define RETOUCH_COMMAND_DEFAULT_HPP
#include "command_core.hpp"

/*
create a new repository on the command line
echo "# empty" >> README.md
git init
git add README.md
git commit -m "first commit"
git branch -M main
git remote add origin https://github.com/ammatwain/empty.git
git push -u origin main

...or push an existing repository from the command line

git remote add origin https://github.com/ammatwain/empty.git
git branch -M main
git push -u origin main
*/

class CommandDefault: public CommandCore
{
public:
    CommandDefault(CommandCore* aCommandCore): CommandCore("", aCommandCore)
    {

    }

    int parse() override
    {
        cxxopts::ParseResult result = this->parseOptions();
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

        return 0;
    }
};

#endif //RETOUCH_COMMAND_DEFAULT_HPP
