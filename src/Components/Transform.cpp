/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** Transform
*/

#include "Transform.hpp"

Components::Transform::Transform(GameObject *gameObject)
    : Component(gameObject)
{
    _position = Vector3Zero();
    _rotation = Vector3Zero();
    _scale = {1, 1, 1};
}

Components::Transform::~Transform()
{
}

void Components::Transform::Translate(Vector3 vec)
{
    _position = Vector3Add(_position, vec);
}

void Components::Transform::Rotate(Vector3 vec)
{
    _rotation = Vector3Add(_rotation, vec);
}

Vector3 Components::Transform::GetPosition() const
{
    return _position;
}

void Components::Transform::SetPosition(Vector3 pos)
{
    _position = pos;
}

void Components::Transform::SetPosition(float x, float y, float z)
{
    _position = {x, y, z};
}

Vector3 Components::Transform::GetRotation() const
{
    return _rotation;
}

void Components::Transform::SetRotation(Vector3 rotation)
{
    _rotation = rotation;
}

void Components::Transform::SetRotation(float x, float y, float z)
{
    _rotation = {x, y, z};
}

Vector3 Components::Transform::GetScale() const
{
    return _scale;
}

void Components::Transform::SetScale(Vector3 scale)
{
    _scale = scale;
}

void Components::Transform::SetScale(float x, float y, float z)
{
    _scale = {x, y, z};
}