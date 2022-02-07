/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** Object
*/

#include "Object.hpp"

static UUIDv4::UUIDGenerator<std::mt19937_64> uuidGenerator;

namespace hr {
    Object::Object()
    {
        _uuid = uuidGenerator.getUUID();
    }

    Object::~Object()
    {

    }

    std::string Object::GetName() const
    {
        return _name;
    }

    void Object::SetName(const std::string &name)
    {
        _name = name;
    }

    UUIDv4::UUID Object::GetUUID() const
    {
        return _uuid;
    }

    void Object::SetUUID(const std::string &str)
    {
        _uuid = UUIDv4::UUID::fromStrFactory(str);
    }

    bool Object::IsActive() const
    {
        return _active;
    }

    void Object::SetActive(bool active)
    {
        _active = active;
    }
}