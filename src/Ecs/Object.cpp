/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** Object
*/

#include "Object.hpp"

static UUIDv4::UUIDGenerator<std::mt19937_64> uuidGenerator;

hr::Object::Object()
{
    _uuid = uuidGenerator.getUUID();
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

UUIDv4::UUID hr::Object::GetUUID() const
{
    return _uuid;
}

bool hr::Object::IsActive() const
{
    return _active;
}

void hr::Object::SetActive(bool active)
{
    _active = active;
}