/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** DisplayManager
*/

#include "DisplayManager.hpp"
#include "Master3DRenderer.hpp"

namespace hr {
    DisplayManager *DisplayManager::instance = nullptr;

    DisplayManager::DisplayManager()
    {
        _renderTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
    }

    DisplayManager::~DisplayManager()
    {
    }

    void DisplayManager::Start()
    {
        Master3DRenderer::Get()->Start();
        _imGuiLayer.Start();
    }

    void DisplayManager::Clear(Color color)
    {
        ClearBackground(color);
    }

    void DisplayManager::Draw()
    {
        if (IsWindowResized()) {
            UnloadRenderTexture(_renderTexture);
            _renderTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
        }

        BeginTextureMode(_renderTexture);
        ClearBackground(DARKBLUE);
        Master3DRenderer::Get()->Draw();
        DrawText(std::to_string(GetFPS()).c_str(), 0, 0, 50, RED);
        EndTextureMode();

        _imGuiLayer.Draw();

    }

    RenderTexture DisplayManager::GetRenderTexture() const
    {
        return _renderTexture;
    }

    Texture *DisplayManager::GetFrameBufferTexture()
    {
        return &(_renderTexture.texture);
    }

    void DisplayManager::End()
    {
        Master3DRenderer::Get()->End();
        _imGuiLayer.End();
        UnloadRenderTexture(_renderTexture);
    }
}