/*
** EPITECH PROJECT, 2021
** 3D
** File description:
** Light
*/

#include "Light.hpp"

IS::LightValue::LightValue(Vector3 position, Color color)
{
    _position = position;
    _color = color;
}

IS::LightValue::~LightValue()
{
}

Vector3 IS::LightValue::getPosition() const
{
    return (_position);
}

Color IS::LightValue::getColor() const
{
    return (_color);
}

void IS::LightValue::setPosition(Vector3 position)
{
    _position = position;
}

void IS::LightValue::setColor(Color color)
{
    _color = color;
}