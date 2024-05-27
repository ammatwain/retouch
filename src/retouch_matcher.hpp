#ifndef RETOUCH_MATCHER_HPP
#define RETOUCH_MATCHER_HPP

//#include <cassert>
//#include <functional>
//#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <utility>
#include <vector>
#include <filesystem>
#include <iostream>
#include "retouch_utils.hpp"

namespace fs = std::filesystem;

class Matcher{
public:
    Matcher(std::string aPattern = "")
    {
        if (aPattern !=  "") {
            this->addPattern(aPattern);
        }
    }

    Matcher& addPattern(std::string aPattern)
    {
        this->privMap.push_back(std::make_pair(aPattern, Matcher::compile_pattern(aPattern)));
        return *this;
    }

    bool match(const std::string &name) {
        for(int i = 0 ; i < this->privMap.size() ; i++){
            //std::cout <<"REGEX " << translate(this->privMap[i].first) << std::endl;
            if ((std::regex_match(name, this->privMap[i].second))) {
                return true;
            }
        }
        return false;
    }

private:
    static inline
        bool string_replace(std::string &str, const std::string &from, const std::string &to) {
        std::size_t start_pos = str.find(from);
        if (start_pos == std::string::npos)
            return false;
        str.replace(start_pos, from.length(), to);
        return true;
    }
    static inline
        std::string translate(const std::string &pattern) {
        return pattern;
    }

    static inline
        std::string _translate(const std::string &pattern) {
        std::size_t i = 0, n = pattern.size();
        std::string result_string;

        while (i < n) {
            auto c = pattern[i];
            i += 1;
            if (c == '*') {
                result_string += ".*";
            } else if (c == '?') {
                result_string += ".";
            } else if (c == '[') {
                auto j = i;
                if (j < n && pattern[j] == '!') {
                    j += 1;
                }
                if (j < n && pattern[j] == ']') {
                    j += 1;
                }
                while (j < n && pattern[j] != ']') {
                    j += 1;
                }
                if (j >= n) {
                    result_string += "\\[";
                } else {
                    auto stuff = std::string(pattern.begin() + i, pattern.begin() + j);
                    if (stuff.find("--") == std::string::npos) {
                        Matcher::string_replace(stuff, std::string{"\\"}, std::string{R"(\\)"});
                    } else {
                        std::vector<std::string> chunks;
                        std::size_t k = 0;
                        if (pattern[i] == '!') {
                            k = i + 2;
                        } else {
                            k = i + 1;
                        }

                        while (true) {
                            k = pattern.find("-", k, j);
                            if (k == std::string::npos) {
                                break;
                            }
                            chunks.push_back(std::string(pattern.begin() + i, pattern.begin() + k));
                            i = k + 1;
                            k = k + 3;
                        }

                        chunks.push_back(std::string(pattern.begin() + i, pattern.begin() + j));
                        // Escape backslashes and hyphens for set difference (--).
                        // Hyphens that create ranges shouldn't be escaped.
                        bool first = false;
                        for (auto &s : chunks) {
                            Matcher::string_replace(s, std::string{"\\"}, std::string{R"(\\)"});
                            Matcher::string_replace(s, std::string{"-"}, std::string{R"(\-)"});
                            if (first) {
                                stuff += s;
                                first = false;
                            } else {
                                stuff += "-" + s;
                            }
                        }
                    }

                    // Escape set operations (&&, ~~ and ||).
                    std::string result;
                    std::regex_replace(std::back_inserter(result),          // result
                                       stuff.begin(), stuff.end(),          // string
                                       std::regex(std::string{R"([&~|])"}), // pattern
                                       std::string{R"(\\\1)"});             // repl
                    stuff = result;
                    i = j + 1;
                    if (stuff[0] == '!') {
                        stuff = "^" + std::string(stuff.begin() + 1, stuff.end());
                    } else if (stuff[0] == '^' || stuff[0] == '[') {
                        stuff = "\\\\" + stuff;
                    }
                    result_string = result_string + "[" + stuff + "]";
                }
            } else {
                // SPECIAL_CHARS
                // closing ')', '}' and ']'
                // '-' (a range in character set)
                // '&', '~', (extended character set operations)
                // '#' (comment) and WHITESPACE (ignored) in verbose mode
                static std::string special_characters = "()[]{}?*+-|^$\\.&~# \t\n\r\v\f";
                static std::map<int, std::string> special_characters_map;
                if (special_characters_map.empty()) {
                    for (auto &sc : special_characters) {
                        special_characters_map.insert(
                            std::make_pair(static_cast<int>(sc), std::string{"\\"} + std::string(1, sc)));
                    }
                }

                if (special_characters.find(c) != std::string::npos) {
                    result_string += special_characters_map[static_cast<int>(c)];
                } else {
                    result_string += c;
                }
            }
        }
        return std::string{"(("} + result_string + std::string{R"()|[\r\n])$)"};
    }

    static inline
        std::regex compile_pattern(const std::string &pattern) {
        //return std::regex(Matcher::translate(pattern), std::regex::extended);
        return std::regex(Matcher::translate(pattern), std::regex::ECMAScript);
    }

    static inline
        bool fnmatch(const fs::path &name, const std::string &pattern) {
        return std::regex_match(name.string(), Matcher::compile_pattern(pattern));
    }

private:
    std::vector<std::pair<std::string,std::regex>> privMap;
};


#endif //RETOUCH_MATCHER_HPP
