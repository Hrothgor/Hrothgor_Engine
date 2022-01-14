/*
** EPITECH PROJECT, 2021
** B-YEP-400-MPL-4-1-indiestudio-cyril.grosjean
** File description:
** Button
*/

#include "Button.hpp"

IS::Button::Button(std::string texture_path, Vector2 pos, void (IS::Button::*func)(void), int nbFrame)
{
    _texture = LoadTexture(texture_path.c_str());
    _rect = {0, 0, (float) _texture.width / nbFrame, (float) _texture.height};
    _position = pos;
    _nbFrame = nbFrame;
    _func = func;
}

IS::Button::~Button()
{
}

void IS::Button::callFunction()
{
    if (_func != nullptr)
        (this->*_func)();
}

void IS::Button::update()
{
    _rect.x = 0;
    Rectangle rect = {_position.x, _position.y, _texture.width / _nbFrame * _scale, _texture.height * _scale};

    if (CheckCollisionPointRec(GetMousePosition(), rect)) {
        _rect.x = _texture.width / _nbFrame;
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
            _rect.x = _texture.width / _nbFrame * 2;
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
            callFunction();
    }
}

void IS::Button::quitButton()
{
    exit(0); //A changer
}

void IS::Button::increasePosition(Vector2 position)
{
    _position = Vector2Add(_position, position);
}

void IS::Button::increaseRotation(float rotation)
{
    _rotation += rotation;
}

void IS::Button::increaseScale(float scale)
{
    _scale += scale;
}

void IS::Button::setPosition(Vector2 position)
{
    _position = position;
}

void IS::Button::setRotation(float rotation)
{
    _rotation = rotation;
}

void IS::Button::setScale(float scale)
{
    _scale = scale;
}

Texture2D IS::Button::getTexture() const
{
    return (_texture);
}

Vector2 IS::Button::getPosition() const
{
    return (_position);
}

float IS::Button::getRotation() const
{
    return (_rotation);
}

float IS::Button::getScale() const
{
    return (_scale);
}

Rectangle IS::Button::getRect() const
{
    return (_rect);
}