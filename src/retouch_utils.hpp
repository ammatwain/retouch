#ifndef RETOUCH_UTILS_HPP
#define RETOUCH_UTILS_HPP
#include <string>
#include <filesystem>

using namespace std::literals;

namespace Retouch
{
const std::string DIRSEP = &std::filesystem::path::preferred_separator;

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

static bool endsWith(std::string_view str, std::string_view suffix)
{
    return str.size() >= suffix.size() && str.compare(str.size()-suffix.size(), suffix.size(), suffix) == 0;
}
static bool endsWith(std::string_view str, char csuffix)
{
    std::string suffix = ""; suffix += csuffix;
    return str.size() >= suffix.size() && str.compare(str.size()-suffix.size(), suffix.size(), suffix) == 0;
}

static bool startsWith(std::string_view str, char cprefix)
{

    std::string prefix = ""; prefix += cprefix;
    return str.size() >= prefix.size() && str.compare(0, prefix.size(), prefix) == 0;
}

};

#endif //RETOUCH_UTILS_HPP
