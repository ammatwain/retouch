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
    CommandDefault(CommandCore* aCommandCore): CommandCore("default", aCommandCore)
    {

    }

    void parse()
    {
        cxxopts::ParseResult result = this->parseOptions();
        std::cout << "PARSING DEFAULT" << std::endl;

    }

};

#endif //RETOUCH_COMMAND_DEFAULT_HPP
