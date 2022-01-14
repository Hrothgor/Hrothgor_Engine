/*
** EPITECH PROJECT, 2021
** B-YEP-400-MPL-4-1-indiestudio-cyril.grosjean
** File description:
** ButtonsRenderer
*/

#include "ButtonsRenderer.hpp"

IS::ButtonsRenderer::ButtonsRenderer()
{
}

IS::ButtonsRenderer::~ButtonsRenderer()
{
}

void IS::ButtonsRenderer::addButton(int scene, Button *button)
{
    for (auto &list : _buttons) {
        if (list.first == scene) {
            list.second.push_back(button);
            return;
        }
    }
    _buttons[scene] = std::vector<Button *> { button };
}

void IS::ButtonsRenderer::init()
{
}

void IS::ButtonsRenderer::render(int scene)
{
    if (_buttons.empty())
        init();
    for (auto &list : _buttons) {
        if (list.first != scene)
            continue;
        for (Button *button : list.second) {
            button->update();
            Rectangle source = button->getRect();
            Rectangle dest = { button->getPosition().x, button->getPosition().y, source.width*button->getScale(), source.height*button->getScale() };
            Vector2 origin = { 0.0, 0.0 };
            DrawTexturePro(button->getTexture(), source, dest, origin, button->getRotation(), WHITE);
        }
    }
}