/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** Object
*/

#include "Object.hpp"

Object::Object()
{

}

Object::~Object()
{

}

std::string Object::GetName() const
{
    return _name;
}

bool Object::IsActive() const
{
    return _active;
}

void Object::SetActive(bool active)
{
    _active = active;
}