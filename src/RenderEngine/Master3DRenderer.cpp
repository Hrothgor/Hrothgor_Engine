/*
** EPITECH PROJECT, 2022
** Hrothgor_Engine
** File description:
** Master3DRenderer
*/

#include "Master3DRenderer.hpp"
#include "Ecs/GameObject.hpp"
#include "Ecs/Engine.hpp"

#include "Components/MainCamera3D.hpp"

namespace hr {
    Master3DRenderer *Master3DRenderer::instance = nullptr;

    Master3DRenderer::Master3DRenderer()
    {
        _renderTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
    }

    Master3DRenderer::~Master3DRenderer()
    {
    }

    void Master3DRenderer::Start()
    {
        _imGuiLayer.Start();

        _camera = Engine::Get()->GetMainCamera()->GetComponent<MainCamera3D>();
        _entityRenderer.Start();
        _particleRenderer.Start();
        _gizmosRenderer.Start();
    }

    void Master3DRenderer::Clear(Color color)
    {
        ClearBackground(color);
    }

    void Master3DRenderer::BeginFrame()
    {
        BeginMode3D(_camera->GetCamera3D());
    }

    void Master3DRenderer::EndFrame()
    {
        EndMode3D();
    }

    void Master3DRenderer::Draw()
    {
        if (IsWindowResized()) {
            UnloadRenderTexture(_renderTexture);
            _renderTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
        }

        BeginTextureMode(_renderTexture);
            ClearBackground(DARKBLUE);
            BeginFrame();
                _entityRenderer.Draw();
                _particleRenderer.Draw();
                _gizmosRenderer.Draw();
            EndFrame();
            DrawText(std::to_string(GetFPS()).c_str(), 0, 0, 50, RED);
        EndTextureMode();
        
        _imGuiLayer.Draw();
    }

    void Master3DRenderer::RegisterGizmos(GameObject *object)
    {
        _gizmosRenderer.RegisterObject(object);
    }

    void Master3DRenderer::RegisterObject(GameObject *model)
    {
        _entityRenderer.RegisterObject(model);
    }

    void Master3DRenderer::RegisterLight(GameObject *light)
    {
        _entityRenderer.RegisterLight(light);
    }

    void Master3DRenderer::RegisterParticle(Particle *particles)
    {
        _particleRenderer.RegisterParticle(particles);
    }

    RenderTexture Master3DRenderer::GetRenderTexture() const
    {
        return _renderTexture;
    }

    Texture *Master3DRenderer::GetFrameBufferTexture()
    {
        return &(_renderTexture.texture);
    }

    void Master3DRenderer::End()
    {
        _imGuiLayer.End();

        _entityRenderer.End();
        _particleRenderer.End();
        _gizmosRenderer.End();

        UnloadRenderTexture(_renderTexture);
    }
}