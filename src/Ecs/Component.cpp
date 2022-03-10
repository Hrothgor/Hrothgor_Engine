/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** Component
*/

#include "Component.hpp"
#include "GameObject.hpp"

namespace hr {
    Component::Component(GameObject *gameObject)
        : _gameObject(gameObject)
    {
        if (_gameObject)
            _transform = _gameObject->GetTransform();
        _name = "Component";
    }

    Component::~Component()
    {
    }

    GameObject *Component::GetGameObject() const
    {
        return _gameObject;
    }

    Transform *Component::GetTransform() const
    {
        return _transform;
    }
}