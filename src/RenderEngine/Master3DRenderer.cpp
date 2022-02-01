/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** Master3DRenderer
*/

#include "Master3DRenderer.hpp"
#include "../Ecs/GameObject.hpp"
#include "../Ecs/Engine.hpp"

#include "../Components/MainCamera3D.hpp"

hr::Master3DRenderer *hr::Master3DRenderer::instance = nullptr;

hr::Master3DRenderer::Master3DRenderer()
{
    _camera = Engine::Get()->FindObjectOfType<MainCamera3D>();
}

hr::Master3DRenderer::~Master3DRenderer()
{
}

void hr::Master3DRenderer::Start()
{
    BeginMode3D(_camera->GetCamera3D());
}

void hr::Master3DRenderer::End()
{
    EndMode3D();
}

void hr::Master3DRenderer::Draw()
{
    Start();
    DrawGrid(100, 1.0f);
    _entityRenderer.Draw();
    //draw particles
    End();
}

void hr::Master3DRenderer::RegisterObject(GameObject *model)
{
    _entityRenderer.RegisterObject(model);
}

void hr::Master3DRenderer::RegisterLight(GameObject *light)
{
    _entityRenderer.RegisterLight(light);
}
