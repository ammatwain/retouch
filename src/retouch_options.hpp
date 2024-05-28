#ifndef RETOUCH_OPTIONS_HPP
#define RETOUCH_OPTIONS_HPP

#include "retouch_command_core.hpp"
#include "retouch_command_default.hpp"
#include "retouch_command_init.hpp"

namespace Retouch
{

class Options
{
public:
    Options(int argc, const char* argv[])
    {
        this->privateCommandCore = new Retouch::Command::Core(argc, argv);
        this->privateCommandDefault = new Retouch::Command::Default(this->privateCommandCore);
        this->privateCommandInit = new Retouch::Command::Init(this->privateCommandCore);
        this->privateCommandCore->parse();
    }
    ~Options()
    {
        delete this->privateCommandInit;
        delete this->privateCommandDefault;
        delete this->privateCommandCore;
    }
private:
    Retouch::Command::Core*    privateCommandCore;
    Retouch::Command::Default* privateCommandDefault;
    Retouch::Command::Init*    privateCommandInit;
};

} //  namespace Retouch

#endif // RETOUCH_OPTIONS_HPP
