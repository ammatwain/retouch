#ifndef RETOUCH_UTILS_HPP
#define RETOUCH_UTILS_HPP
#include <string>
#include <filesystem>
#include <cstdio>
//#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

using namespace std::literals;

namespace Retouch
{

const std::string DIRSEP = &std::filesystem::path::preferred_separator;

/*
inline static bool ends_with(std::string const & value, std::string const & ending)
{
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

inline static bool ends_with(std::string const & value, char const & cending)
{
    std::string ending = ""; ending += cending;
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}
*/

std::string basename(std::string const & path)
{
    return path.substr(path.find_last_of("/\\") + 1);
}

static bool endsWith(std::string_view str, std::string_view suffix)
{
    return str.size() >= suffix.size() && str.compare(str.size()-suffix.size(), suffix.size(), suffix) == 0;
}

static bool endsWith(std::string_view str, char csuffix)
{
    std::string suffix = &csuffix;
    return str.size() >= suffix.size() && str.compare(str.size()-suffix.size(), suffix.size(), suffix) == 0;
}

std::string execute(const std::string cmd) {
    std::array<char, 128> buffer;
    std::string result;
    //std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    std::unique_ptr<FILE, void(*)(FILE*)> pipe(
        popen(cmd.c_str(), "r"),
        [](FILE * f) -> void {
            // wrapper to ignore the return value from pclose() is needed with newer versions of gnu g++
            std::ignore = pclose(f);
        }
    );
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }

    while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

static bool startsWith(std::string_view str, char cprefix)
{

    std::string prefix = &cprefix;
    return str.size() >= prefix.size() && str.compare(0, prefix.size(), prefix) == 0;
}

}; // namespace Retouch

#endif //RETOUCH_UTILS_HPP
