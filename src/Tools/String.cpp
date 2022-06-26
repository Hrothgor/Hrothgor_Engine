/*
** EPITECH PROJECT, 2022
** Hrothgor_Engine
** File description:
** String
*/

#include "String.hpp"

namespace hr
{
    bool String::EndWith(std::string const &value, std::string const &ending)
    {
        if (ending.size() > value.size()) return false;
        return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
    }

    std::string String::NameByPath(std::string const &path)
    {
        std::string name = path;
        size_t pos = name.find_last_of("/\\");
        if (pos != std::string::npos)
            name = name.substr(pos + 1);
        return name;
    }
}