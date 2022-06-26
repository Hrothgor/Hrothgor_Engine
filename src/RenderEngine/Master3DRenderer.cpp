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

#include "PhysicsEngine/PhysicsWorld.hpp"

namespace hr {
    Master3DRenderer *Master3DRenderer::instance = nullptr;

    Master3DRenderer::Master3DRenderer()
    {
    }

    Master3DRenderer::~Master3DRenderer()
    {
    }

    void Master3DRenderer::Start()
    {
        _camera = Engine::Get()->GetMainCamera()->GetComponent<MainCamera3D>();
        _entityRenderer.Start();
        _particleRenderer.Start();
        _gizmosRenderer.Start();
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
        BeginFrame();
        _entityRenderer.Draw();
        _particleRenderer.Draw();
        _gizmosRenderer.Draw();
        PhysicsWorld::Get()->Update();
        EndFrame();
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

    void Master3DRenderer::End()
    {
        _entityRenderer.End();
        _particleRenderer.End();
        _gizmosRenderer.End();
    }
}