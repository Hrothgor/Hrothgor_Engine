/*
** EPITECH PROJECT, 2022
** indieStudio
** File description:
** EntityRenderer
*/

#include "EntityRenderer.hpp"
#include "../Ecs/Engine.hpp"
#include "../Ecs/GameObject.hpp"

#include "../Components/Transform.hpp"
#include "../Components/MeshRenderer.hpp"
#include "../Components/Light.hpp"
#include "../Components/MainCamera3D.hpp"

namespace hr {
    EntityRenderer::EntityRenderer()
    {
    }

    EntityRenderer::~EntityRenderer()
    {
    }

    void EntityRenderer::Start()
    {
        _camera = Engine::Get()->GetMainCamera()->GetComponent<MainCamera3D>();
    }

    void EntityRenderer::BeginFrame()
    {
        _lightShader.UpdateLightsLoc(_lights);
        _lightShader.UpdateCameraLoc(_camera->GetCamera3D());
    }

    void EntityRenderer::Draw()
    {
        BeginFrame();
        for (GameObject *object : _objects) {
            Transform *transform = object->GetTransform();
            MeshRenderer *meshRenderer = object->GetComponent<MeshRenderer>();
            for (int i = 0; i < meshRenderer->GetModel().materialCount; i++)
                meshRenderer->GetModel().materials[i].shader = _lightShader.GetShader();
            AxisAngle axisAngle = transform->GetRotationAxisAngle();
            DrawModelEx(meshRenderer->GetModel(), transform->GetPositionWorld(), axisAngle.axis, axisAngle.angle, transform->GetScale(), WHITE);
        }
        EndFrame();
    }

    void EntityRenderer::EndFrame()
    {
        _objects.clear();
        _lights.clear();
    }

    void EntityRenderer::RegisterLight(GameObject *light)
    {
        _lights.push_back(light);
    }

    void EntityRenderer::RegisterObject(GameObject *object)
    {
        _objects.push_back(object);
    }

    void EntityRenderer::End()
    {
        UnloadShader(_lightShader.GetShader());
    }
}