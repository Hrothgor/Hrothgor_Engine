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

Master3DRenderer *Master3DRenderer::instance = nullptr;

Master3DRenderer::Master3DRenderer()
{
    _camera = Engine::Get()->FindObjectOfType<Components::MainCamera3D>();
}

Master3DRenderer::~Master3DRenderer()
{
}

void Master3DRenderer::Start()
{
    BeginMode3D(_camera->GetCamera3D());
}

void Master3DRenderer::End()
{
    EndMode3D();
}

void Master3DRenderer::Draw()
{
    Start();
    DrawGrid(100, 1.0f);
    _entityRenderer.Draw();
    //draw particles
    End();
}

void Master3DRenderer::RegisterObject(GameObject *model)
{
    _entityRenderer.RegisterObject(model);
}

void Master3DRenderer::RegisterLight(GameObject *light)
{
    _entityRenderer.RegisterLight(light);
}
