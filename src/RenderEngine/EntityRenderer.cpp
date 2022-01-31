/*
** EPITECH PROJECT, 2022
** indieStudio
** File description:
** EntityRenderer
*/

#include "EntityRenderer.hpp"
#include "../Ecs/GameObject.hpp"
#include "../Components/Transform.hpp"
#include "../Components/MeshRenderer.hpp"

EntityRenderer::EntityRenderer()
{
}

EntityRenderer::~EntityRenderer()
{
}


void EntityRenderer::Start()
{
    // for (Light &light : _lights)
        // UpdateLightValues(_lightShader.getShader(), light);
}

void EntityRenderer::Draw()
{
    Start();
    for (GameObject *object : _objects) {
        Components::Transform *transform = object->GetTransform();
        Components::MeshRenderer *meshRenderer = object->GetComponent<Components::MeshRenderer>();
        DrawModelEx(meshRenderer->GetModel(), transform->GetPosition(), Vector3Zero(), 0, transform->GetScale(), WHITE);
    }
    End();
}

void EntityRenderer::End()
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