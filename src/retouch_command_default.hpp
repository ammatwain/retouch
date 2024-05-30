#ifndef RETOUCH_COMMAND_DEFAULT_HPP
#define RETOUCH_COMMAND_DEFAULT_HPP
#include "retouch_command_core.hpp"

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

namespace Retouch{

namespace Command{


class Default: public Retouch::Command::Core
{
public:
    Default(Retouch::Command::Core* aCommandCore): Retouch::Command::Core("", aCommandCore)
    {

    }

    int parse() override
    {
        int error = 0;
        cxxopts::ParseResult result = this->parseOptions();
        error = preParseCommon(result);
        if (!error){

        }
        return error;
    }
};

} //namespace Retouch::Command

} //namespace Retouch

#endif //RETOUCH_COMMAND_DEFAULT_HPP
