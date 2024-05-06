#include "opzioni.h"

Opzioni::Opzioni(Opzioni* aParent)
{
    this->privateParent = aParent;
}

void Opzioni::addOpzione(ArgType aArgType, std::string aLongName, std::string aDefaultValue) {
    Opzione* opzione = new Opzione(aArgType,aLongName,aDefaultValue);
    this->privateVectorOpzione.push_back(opzione);
}

void Opzioni::addOpzione(ArgType aArgType, std::string aLongName, std::string aDefaultValue, std::string aHelp) {
    Opzione* opzione = new Opzione(aArgType,aLongName,aDefaultValue,aHelp);
    this->privateVectorOpzione.push_back(opzione);
}

void Opzioni::addOpzione(ArgType aArgType, std::string aLongName,  std::string aShortName, std::string aDefaultValue, std::string aHelp) {
    Opzione* opzione = new Opzione(aArgType,aLongName,aShortName,aDefaultValue,aHelp);
    this->privateVectorOpzione.push_back(opzione);
}

void Opzioni::analizeTokens() {

}

void Opzioni::passArguments(int argc, char *argv[])
{
    this->privateCommand.clear();
    this->privateArgv.clear();
    this->privateToken.clear();
    if (argc>0) {
        this->privateCommand = argv[0];
        for(int i = 1; i < argc ; i++) {
            this->privateArgv.push_back(argv[i]);
        }
        for(int i = 0; i < this->privateArgv.size() ; i++) {
            this->scanToken(this->privateArgv[i]);
        }
    }
}

void Opzioni::scanToken(std::string token)
{
    if (token == "---")
    {
        this->privateToken.push_back(token);
    }
    else if (token == "--")
    {
        this->privateToken.push_back(token);
    }
    else if (token == "-")
    {
        this->privateToken.push_back(token);
    }
    else if (token == "+")
    {
        this->privateToken.push_back(token);
    }
    else if (token.rfind("---", 0) == 0)
    {
        this->privateToken.push_back(token);
    }
    else if (token.rfind("--", 0) == 0)
    {
        this->privateToken.push_back(token);
    }
    else if (token.rfind("-", 0) == 0)
    {
        for (int i = 1 ; i < token.size() ; i++) {
            std::string tmpToken = "-";
            tmpToken += token[i];
            this->privateToken.push_back(tmpToken);
        }
    }
    else if (token.rfind("+", 0) == 0)
    {
        this->privateToken.push_back(token);
    }
    else
    {
        this->privateToken.push_back(token);
    }
 }
