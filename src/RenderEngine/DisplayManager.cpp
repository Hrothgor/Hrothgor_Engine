/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** DisplayManager
*/

#include "DisplayManager.hpp"

DisplayManager *DisplayManager::instance = nullptr;

DisplayManager::DisplayManager()
{
}

DisplayManager::~DisplayManager()
{
}

void DisplayManager::Clear(Color color)
{
    ClearBackground(color);
}

void DisplayManager::Draw()
{
    Master3DRenderer::Get()->Draw();
    Master2DRenderer::Get()->Draw();
}