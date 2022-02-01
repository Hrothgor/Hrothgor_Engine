/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** DisplayManager
*/

#include "DisplayManager.hpp"

hr::DisplayManager *hr::DisplayManager::instance = nullptr;

hr::DisplayManager::DisplayManager()
{
}

hr::DisplayManager::~DisplayManager()
{
}

void hr::DisplayManager::Clear(Color color)
{
    ClearBackground(color);
}

void hr::DisplayManager::Draw()
{
    Master3DRenderer::Get()->Draw();
    Master2DRenderer::Get()->Draw();
}