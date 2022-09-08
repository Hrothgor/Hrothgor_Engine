/*
** EPITECH PROJECT, 2022
** indieStudio
** File description:
** EntityRenderer
*/

#include "EntityRenderer.hpp"
#include "Ecs/Engine.hpp"
#include "Ecs/GameObject.hpp"

#include "Components/Transform.hpp"
#include "Components/MeshRenderer.hpp"
#include "Components/Light.hpp"
#include "Components/MainCamera3D.hpp"

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

            Model model = meshRenderer->GetModel();
            Texture texture = meshRenderer->GetTexture();
            AxisAngle axisAngle = transform->GetRotationAxisAngle();
            
            for (int i = 0; i < model.materialCount; i++)
                model.materials[i].shader = _lightShader.GetShader();
            if (model.materialCount > 0 && texture.id != 0)
                SetMaterialTexture(&(model.materials[0]), MATERIAL_MAP_DIFFUSE, texture);
            else if (model.materialCount > 0)
                SetMaterialTexture(&(model.materials[0]), MATERIAL_MAP_DIFFUSE, (Texture2D){ rlGetTextureIdDefault(), 1, 1, 1, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8 });

            rlEnableBackfaceCulling();
            if (meshRenderer->GetHasTransparency())
                rlDisableBackfaceCulling();

            DrawModelEx(model, transform->GetPositionWorld(), axisAngle.axis, axisAngle.angle, transform->GetScaleWorld(), meshRenderer->GetColor());
        }
        EndFrame();
    }

    void EntityRenderer::EndFrame()
    {
        _objects.clear();
        _lights.clear();
        rlEnableBackfaceCulling();
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
        _lightShader.End();
    }
}