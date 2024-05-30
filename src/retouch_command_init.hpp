#ifndef RETOUCH_COMMAND_INIT_HPP
#define RETOUCH_COMMAND_INIT_HPP
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

class Init: public Retouch::Command::Core
{
public:
    Init(Retouch::Command::Core* aCommandCore)
        : Retouch::Command::Core("init", aCommandCore)
    {
        this->options()->add_options()
            ("d,directory","(Local path retouch repository)", cxxopts::value<std::string>(),"<FOLDER>")
            ("o,original","(Original github repository)", cxxopts::value<std::string>(),"<URL>")
            ("m,modified","(Modified github repository)", cxxopts::value<std::string>(),"<URL>")
        ;
        /*
        */
    }
    int parse() override
    {
        int error = 0;
        cxxopts::ParseResult result = this->parseOptions();
        error = preParseCommon(result);
        if (!error){
            alert("1");
            if (!this->projectExists())
            {
                alert("2");
                if(!this->workDirExists())
                {
                    alert(this->workDir());
                    std::filesystem::create_directory(this->workDir());
                }
                alert("3");
                if(this->workDirExists())
                {
                    alert("3a");
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
                                /*
                                if(!this->retouchConfigFileExists())
                                {

                                }
                                if(this->retouchConfigFileExists())
                                {

                                }
                                */
                            }
                        }
                    }
                }
            } else {
                this->alert("Retoruch project already exists.");
            }
        }
        return error;
    }

};

} //namespace Retouch::Command

} //namespace Retouch


#endif //RETOUCH_COMMAND_INIT_HPP
