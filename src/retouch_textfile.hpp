#ifndef RETOUCH_CONSOLE_CURSOR_HPP
#define RETOUCH_CONSOLE_CURSOR_HPP

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

// INTERFACE
namespace Retouch
{

class TextFile {
public:
    std::string getContents(std::string fileName);
    bool putContents(std::string fileName, std::string str);
};

// IMPLEMENTATION

std::string TextFile::getContents(std::string fileName) {
    std::ifstream inputFile(fileName);
    // check if the file was opened successfully
    if (inputFile.is_open())
    {
        std::stringstream stringStream;
        stringStream << inputFile.rdbuf(); //read the file
        return stringStream.str(); //str holds the content of the file
    }
    return "";
}


bool TextFile::putContents(std::string fileName, std::string str)
{
    std::ofstream outputFile(fileName);
    // check if the file was opened successfully
    if (outputFile.is_open()) { // check if the file was opened successfully
        outputFile << str; // write data to the file
        outputFile.close(); // close the file when done
        return true;
    }
    return false;
}

} // namespace Retouch

#endif // RETOUCH_CONSOLE_CURSOR_HPP
