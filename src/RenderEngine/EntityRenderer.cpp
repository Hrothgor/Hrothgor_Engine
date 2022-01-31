/*
** EPITECH PROJECT, 2022
** indieStudio
** File description:
** EntityRenderer
*/

#include "EntityRenderer.hpp"

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
        Transform *transform = object->GetTransform();
        Model *model = object->GetComponent<Model>();
        DrawModelEx(*model, transform->translation, Vector3Zero(), 0, transform->scale, WHITE);
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