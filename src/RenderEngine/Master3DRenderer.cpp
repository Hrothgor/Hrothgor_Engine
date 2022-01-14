/*
** EPITECH PROJECT, 2021
** indieStudio
** File description:
** Master3DRenderer
*/

#include "Master3DRenderer.hpp"

IS::Master3DRenderer::Master3DRenderer()
{
}

IS::Master3DRenderer::~Master3DRenderer()
{
}

void IS::Master3DRenderer::start(IS::Camera *camera)
{
    ClearBackground(DARKBLUE);
    BeginMode3D(camera->getCamera3D());
}

void IS::Master3DRenderer::stop()
{
    EndMode3D();
}

void IS::Master3DRenderer::render(int scene, IS::Camera *camera)
{
    start(camera);
    DrawGrid(100, 1.0f);
    {
        _entityRenderer.render(scene, camera);
    }
    {
        rlDisableDepthMask();
        //BeginBlendMode(BLEND_ADDITIVE);
        _particlesRenderer.render(scene, camera);
        //EndBlendMode();
        rlEnableDepthMask();
    }
    stop();
}

void IS::Master3DRenderer::addLight(const LightValue &light)
{
    _entityRenderer.addLight(0, light);
}

void IS::Master3DRenderer::addEntity(int scene, Entity *entity)
{
    _entityRenderer.addEntity(scene, entity);
}

void IS::Master3DRenderer::addParticles(const Particle &particles)
{
    _particlesRenderer.addParticles(particles);
}
