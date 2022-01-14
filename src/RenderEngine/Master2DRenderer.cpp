/*
** EPITECH PROJECT, 2021
** indieStudio
** File description:
** Master2DRenderer
*/

#include "Master2DRenderer.hpp"

IS::Master2DRenderer::Master2DRenderer()
{
}

IS::Master2DRenderer::~Master2DRenderer()
{
}

void IS::Master2DRenderer::start()
{
    // BeginMode2D();
}

void IS::Master2DRenderer::render(int scene)
{
    start();
    DrawText(std::to_string(GetFPS()).c_str(), 0, 0, 50, RED);
    _buttonsRenderer.render(scene);
    stop();
}

void IS::Master2DRenderer::stop()
{
    // EndMode2D();
}