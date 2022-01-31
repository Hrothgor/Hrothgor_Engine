/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** Master3DRenderer
*/

#include "Master3DRenderer.hpp"
#include "../Ecs/Engine.hpp"

Master3DRenderer *Master3DRenderer::instance = nullptr;

Master3DRenderer::Master3DRenderer()
{
    // _camera = Engine::Get()->FindObjectOfType<MainCamera3D>();
}

Master3DRenderer::~Master3DRenderer()
{
}

void Master3DRenderer::Start()
{
    // BeginMode3D(&_camera);
}

void Master3DRenderer::End()
{
    // EndMode3D();
}

void Master3DRenderer::Draw()
{
    Start();
    DrawGrid(100, 1.0f);
    entityRenderer.Draw();
    //draw particles
    End();
}

void Master3DRenderer::RegisterObject(GameObject *model)
{
    entityRenderer.RegisterObject(model);
}

void Master3DRenderer::RegisterLight(GameObject *light)
{
    entityRenderer.RegisterLight(light);
}
