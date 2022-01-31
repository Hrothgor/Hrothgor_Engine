/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** Component
*/

#include "Component.hpp"
#include "GameObject.hpp"
#include "../Components/Transform.hpp"

Component::Component(GameObject *gameObject)
	: _gameObject(gameObject)
{
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

Components::Transform *Component::GetTransform() const
{
    return _transform;
}