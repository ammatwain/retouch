#ifndef __PP_JSON_H__
#define __PP_JSON_H__

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "extern/jsonxx/jsonxx.h"

// INTERFACE

class TextFileInterface {
public:
    std::string getFileContents(std::string fileName);
    bool putFileContents(std::string fileName, std::string str);
};

class RetouchJsonArray: public jsonxx::Array, TextFileInterface {
public:
    bool load(const std::string &filename);
    bool save(const std::string &filename);
};

class RetouchJsonObject: public jsonxx::Object, TextFileInterface {
public:
    bool load(const std::string &filename);
    bool save(const std::string &filename);
};

// IMPLEMENTATION

std::string TextFileInterface::getFileContents(std::string fileName) {
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


bool TextFileInterface::putFileContents(std::string fileName, std::string str)
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

bool RetouchJsonArray::load(const std::string &filename){
    return this->parse(this->getFileContents(filename));
}

bool RetouchJsonArray::save(const std::string &filename){
    return this->putFileContents(filename, this->json());
}

bool RetouchJsonObject::load(const std::string &filename){
    return this->parse(this->getFileContents(filename));
}

bool RetouchJsonObject::save(const std::string &filename){
    return this->putFileContents(filename, this->json());
}

#endif
