#ifndef OPZIONI_H
#define OPZIONI_H
#include <string>
#include <vector>

class Opzioni
{
public:
    std::string privateExecutable;
    std::vector<std::string> privateArgv;
    std::vector<std::string> privateToken;
    Opzioni();
    void passArguments(int argc, char *argv[]);
    void scanToken(std::string token);
};

#endif // OPZIONI_H
