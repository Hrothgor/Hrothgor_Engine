    /*
** EPITECH PROJECT, 2021
** 3D
** File description:
** Transform
*/

#include "Transform.hpp"

IS::Transform::Transform(Vector3 position, Vector3 rotation, float scale)
{
    _position = position;
    _rotation = rotation;
    _scale = scale;
}

IS::Transform::~Transform()
{
}

void IS::Transform::increasePosition(Vector3 vec)
{
    _position.x += vec.x;
    _position.y += vec.y;
    _position.z += vec.z;
}

void IS::Transform::increaseRotation(Vector3 vec)
{
    _rotation.x += vec.x;
    _rotation.y += vec.y;
    _rotation.z += vec.z;
}

Vector3 IS::Transform::getPosition() const
{
    return (_position);
}

Vector3 IS::Transform::getRotation() const
{
    return (_rotation);
}

float IS::Transform::getScale() const
{
    return (_scale);
}

void IS::Transform::setPosition(Vector3 position)
{
    _position = position;
}

void IS::Transform::setRotation(Vector3 rotation)
{
    _rotation = rotation;
}

void IS::Transform::setScale(float scale)
{
    _scale = scale;
}