/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** Component
*/

#include "Component.hpp"
#include "GameObject.hpp"

hr::Component::Component(GameObject *gameObject)
	: _gameObject(gameObject)
{
	_transform = _gameObject->GetTransform();
    _name = "Component";
}

hr::Component::~Component()
{
}

hr::GameObject *hr::Component::GetGameObject() const
{
    return _gameObject;
}

hr::Transform *hr::Component::GetTransform() const
{
    return _transform;
}

void hr::Component::print(std::ostream &os) const
{
    os << "Component: " << _name << std::endl;
}