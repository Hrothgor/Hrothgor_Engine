/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** Object
*/

#include "Object.hpp"

hr::Object::Object()
{

}

hr::Object::~Object()
{

}

std::string hr::Object::GetName() const
{
    return _name;
}

void hr::Object::SetName(const std::string &name)
{
    _name = name;
}

bool hr::Object::IsActive() const
{
    return _active;
}

void hr::Object::SetActive(bool active)
{
    _active = active;
}