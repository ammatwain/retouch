#ifndef OPZIONI_H
#define OPZIONI_H
#include <string>
#include <vector>

enum ArgType {
    ARG_SUBCOM,
    ARG_SINGLE,
    ARG_DOUBLE,
    ARG_VECTOR,
};

class Opzione {
public:

    Opzione(ArgType aArgType, std::string aLongName, std::string aHelp) {
        this->privateArgType = aArgType;
        this->privateLongName = aLongName;
        this->privateDefaultValue = "";
        this->privateHelp = aHelp;
        this->privateShortName = "";
    }

    Opzione(ArgType aArgType, std::string aLongName, std::string aDefaultValue, std::string aHelp) {
        this->privateArgType = aArgType;
        this->privateLongName = aLongName;
        this->privateDefaultValue = aDefaultValue;
        this->privateHelp = aHelp;
        this->privateShortName = "";
    }

    Opzione(ArgType aArgType, std::string aLongName,  std::string aShortName, std::string aDefaultValue, std::string aHelp) {
        this->privateArgType = aArgType;
        this->privateLongName = aLongName;
        this->privateDefaultValue = aDefaultValue;
        this->privateHelp = aHelp;
        this->privateShortName = aShortName;
    }

    ArgType argType() {
        return this->privateArgType;
    }

    std::string longName() {
        return this->privateLongName;
    }

    std::string shortName() {
        return this->privateShortName;
    }

    std::string defaulValue() {
        return this->privateDefaultValue;
    }

    std::string help() {
        return this->privateHelp;
    }

    void setPresenceStatus(bool aPresenceStatus){
        this->privateIsPresent = aPresenceStatus;
    }

    bool isPresent(){
        return this->privateIsPresent;
    }

private:
    ArgType privateArgType;
    std::string privateLongName = "";
    std::string privateShortName = "";
    std::string privateDefaultValue = "";
    std::string privateHelp = "";
    bool privateIsPresent = false;
};

class Opzioni
{
public:
    Opzioni* privateParent;
    std::string privateCommand;
    std::vector<std::string> privateArgv;
    std::vector<std::string> privateToken;
    Opzioni(Opzioni* aParent = nullptr);
    void addOpzione(ArgType aArgType, std::string aLongName, std::string aDefaultValue);
    void addOpzione(ArgType aArgType, std::string aLongName, std::string aDefaultValue, std::string aHelp);
    void addOpzione(ArgType aArgType, std::string aLongName,  std::string aShortName, std::string aDefaultValue, std::string aHelp);
    void passArguments(int argc, char *argv[]);
private:
    void scanToken(std::string token);
    void analizeTokens();
private:
    std::vector<Opzione*> privateVectorOpzione;
};

#endif // OPZIONI_H
