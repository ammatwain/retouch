#ifndef RETOUCH_JSON_HPP
#define RETOUCH_JSON_HPP

#include <string>
#include "retouch_textfile.hpp"
#include "extern/jsonxx/jsonxx.h"

// INTERFACE
namespace Retouch
{

namespace Json
{

class Array: public jsonxx::Array, Retouch::TextFile {
public:
    bool load(const std::string &filename);
    bool save(const std::string &filename);
};

class Object: public jsonxx::Object, Retouch::TextFile {
public:
    bool load(const std::string &filename);
    bool save(const std::string &filename);
};

// IMPLEMENTATION


bool Array::load(const std::string &filename){
    return this->parse(this->getContents(filename));
}

bool Array::save(const std::string &filename){
    return this->putContents(filename, this->json());
}

bool Object::load(const std::string &filename){
    return this->parse(this->getContents(filename));
}

bool Object::save(const std::string &filename){
    return this->putContents(filename, this->json());
}

} // namespace Retouch::Json

} // namespace Retouch

#endif // RETOUCH_JSON_HPP
