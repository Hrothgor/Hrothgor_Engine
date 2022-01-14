/*
** EPITECH PROJECT, 2021
** indieStudio
** File description:
** EntityRenderer
*/

#include "EntityRenderer.hpp"

#define RLIGHTS_IMPLEMENTATION
#include "rlights.h"

IS::EntityRenderer::EntityRenderer()
{
}

IS::EntityRenderer::~EntityRenderer()
{
}


void IS::EntityRenderer::prepare(int scene, Camera *camera)
{
    for (Light &light : _lights) {
        UpdateLightValues(_lightShader.getShader(), light);
        DrawSphere(light.position, 1000, YELLOW);
    }
}

void IS::EntityRenderer::render(int scene, IS::Camera *camera)
{
    prepare(scene, camera);
    for (auto &list : _entities) {
        if (list.first != scene)
            continue;
        for (Entity *entity : list.second) {
            prepareEntity(entity);
            if (!entity->update(camera))
                continue;
            DrawModel(entity->getTexturedModel().getModel(), entity->getPosition(), entity->getScale(), WHITE);
        }
    }
    clear(scene);
}

void IS::EntityRenderer::prepareEntity(Entity *entity)
{
    if (!entity->getTexturedModel().hasShader())
        entity->getTexturedModel().setShader(_lightShader.getShader());
    
    for (int i = 0; i < entity->getTexturedModel().getModel().materialCount; i++)
        entity->getTexturedModel().setColor(entity->getColor(i), i);
}

void IS::EntityRenderer::clear(int scene)
{
    for (auto &list : _entities) {
        list.second.clear();
    }
}

void IS::EntityRenderer::addLight(int scene, const LightValue &light)
{
    _lights.push_back(CreateLight(LIGHT_POINT, light.getPosition(), Vector3Zero(), light.getColor(), _lightShader.getShader()));
}

void IS::EntityRenderer::addEntity(int scene, Entity *entity)
{
    for (auto &list : _entities) {
        if (list.first == scene) {
            list.second.push_back(entity);
            return;
        }
    }
    _entities[scene] = std::vector<Entity *> { entity };
}