/*
** EPITECH PROJECT, 2022
** Physics_engine
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
}