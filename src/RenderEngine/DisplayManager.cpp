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
    _renderTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
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
    if (IsWindowResized()) {
        UnloadRenderTexture(_renderTexture);
        _renderTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
    }

    BeginTextureMode(_renderTexture);
    ClearBackground(DARKBLUE);

    Master3DRenderer::Get()->Draw();
    Master2DRenderer::Get()->Draw();

    EndTextureMode();

    _imGuiLayer.Start();
    _imGuiLayer.Draw();
    _imGuiLayer.End();

}

RenderTexture hr::DisplayManager::GetRenderTexture() const
{
    return _renderTexture;
}

Texture *hr::DisplayManager::GetFrameBufferTexture()
{
    return &(_renderTexture.texture);
}