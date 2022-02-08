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
#include "../Components/PrimitiveRenderer.hpp"
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
            MeshRenderer *meshRenderer = object->TryGetComponent<MeshRenderer>();
            PrimitiveRenderer *primitiveRenderer = object->TryGetComponent<PrimitiveRenderer>();

            Model model;
            if (meshRenderer)
                model = meshRenderer->GetModel();
            else if (primitiveRenderer)
                model = primitiveRenderer->GetModel();
                
            AxisAngle axisAngle = transform->GetRotationAxisAngle();

            for (int i = 0; i < model.materialCount; i++)
                model.materials[i].shader = _lightShader.GetShader();
            DrawModelEx(model, transform->GetPositionWorld(), axisAngle.axis, axisAngle.angle, transform->GetScale(), WHITE);
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