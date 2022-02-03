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

hr::EntityRenderer::EntityRenderer()
{
    _camera = Engine::Get()->FindObjectOfType<MainCamera3D>();
}

hr::EntityRenderer::~EntityRenderer()
{
}


void hr::EntityRenderer::Start()
{
    for (GameObject *object : _lights) {
        Light *light = object->GetComponent<Light>();
        light->UpdateValues(_lightShader.GetShader());
        _lightShader.UpdateCameraLoc(_camera->GetCamera3D());
    }
    // TODO UPDATE ALL LIGHT BECAUSE WHNE THERE IS NO LIGHT IT DONT UPDATE THE LIGHT BUT KEEP THE OLD LIGHT
}

void hr::EntityRenderer::Draw()
{
    Start();
    for (GameObject *object : _objects) {
        Transform *transform = object->GetTransform();
        MeshRenderer *meshRenderer = object->GetComponent<MeshRenderer>();
        for (int i = 0; i < meshRenderer->GetModel().materialCount; i++)
            meshRenderer->GetModel().materials[i].shader = _lightShader.GetShader();
        AxisAngle axisAngle = transform->GetRotationAxisAngle();
        DrawModelEx(meshRenderer->GetModel(), transform->GetPosition(), axisAngle.axis, axisAngle.angle, transform->GetScale(), WHITE);
    }
    End();
}

void hr::EntityRenderer::End()
{
    _objects.clear();
    _lights.clear();
}

void hr::EntityRenderer::RegisterLight(GameObject *light)
{
    _lights.push_back(light);
}

void hr::EntityRenderer::RegisterObject(GameObject *object)
{
    _objects.push_back(object);
}