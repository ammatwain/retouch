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
        */
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

} //namespace Retouch::Command

} //namespace Retouch


#endif //RETOUCH_COMMAND_INIT_HPP
