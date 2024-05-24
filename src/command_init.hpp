#ifndef RETOUCH_COMMAND_INIT_HPP
#define RETOUCH_COMMAND_INIT_HPP
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

class CommandInit: public CommandCore
{
public:
    CommandInit(CommandCore* aCommandCore)
        : CommandCore("init", aCommandCore)
    {
        if(this->projectParentDirExists())
        {
            if (!this->projectExists())
            {
                if(!this->projectDirExists())
                {
                    std::filesystem::create_directory(this->projectDir());
                }
                if(this->projectDirExists())
                {
                    if(!this->retouchDirExists())
                    {
                        std::filesystem::create_directory(this->retouchDir());
                    }
                    if(this->retouchDirExists())
                    {
                        if(!this->originalDirExists())
                        {
                            std::filesystem::create_directory(this->originalDir());
                        }
                        if(this->originalDirExists())
                        {
                            if(!this->modifiedDirExists())
                            {
                                std::filesystem::create_directory(this->modifiedDir());
                            }
                            if(this->modifiedDirExists())
                            {
                                if(!this->retouchConfigFileExists())
                                {

                                }
                                if(this->retouchConfigFileExists())
                                {

                                }

                            }
                        }
                    }
                }
            }
        }
    }
    void parse()
    {
        cxxopts::ParseResult result = this->parseOptions();
        std::cout << "PARSING INIT" << std::endl;

    }

};

#endif //RETOUCH_COMMAND_INIT_HPP
