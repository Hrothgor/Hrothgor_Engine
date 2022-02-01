/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** Master2DRenderer
*/

#include "Master2DRenderer.hpp"
#include "../Ecs/GameObject.hpp"

hr::Master2DRenderer *hr::Master2DRenderer::instance = nullptr;

hr::Master2DRenderer::Master2DRenderer()
{
}

hr::Master2DRenderer::~Master2DRenderer()
{
}

void hr::Master2DRenderer::Start()
{
    // BeginMode2D();
}

void hr::Master2DRenderer::End()
{
    // EndMode2D();
}

void hr::Master2DRenderer::Draw()
{
    Start();
    DrawText(std::to_string(GetFPS()).c_str(), 0, 0, 50, RED);
    End();
}