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
    CommandInit(std::string aModifiedUrl, std::string aProjectPath = std::filesystem::current_path().string())
        : CommandCore(aProjectPath)
    {
        if(this->projectParentPathExists())
        {
            if (!this->projectExists())
            {
                if(!this->projectPathExists())
                {
                    std::filesystem::create_directory(this->projectPath());
                }
                if(this->projectPathExists())
                {
                    if(!this->retouchPathExists())
                    {
                        std::filesystem::create_directory(this->retouchPath());
                    }
                    if(this->retouchPathExists())
                    {
                        if(!this->originalPathExists())
                        {
                            std::filesystem::create_directory(this->originalPath());
                        }
                        if(this->originalPathExists())
                        {
                            if(!this->modifiedPathExists())
                            {
                                std::filesystem::create_directory(this->modifiedPath());
                            }
                            if(this->modifiedPathExists())
                            {
                                if(!this->retouchConfigExists())
                                {

                                }
                                if(this->retouchConfigExists())
                                {

                                }

                            }
                        }
                    }
                }
            }
        }
    }

};

#endif //RETOUCH_COMMAND_INIT_HPP
