/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** Master2DRenderer
*/

#include "Master2DRenderer.hpp"
#include "../Ecs/GameObject.hpp"

Master2DRenderer *Master2DRenderer::instance = nullptr;

Master2DRenderer::Master2DRenderer()
{
}

Master2DRenderer::~Master2DRenderer()
{
}

void Master2DRenderer::Start()
{
    // BeginMode2D();
}

void Master2DRenderer::End()
{
    // EndMode2D();
}

void Master2DRenderer::Draw()
{
    Start();
    DrawText(std::to_string(GetFPS()).c_str(), 0, 0, 50, RED);
    End();
}