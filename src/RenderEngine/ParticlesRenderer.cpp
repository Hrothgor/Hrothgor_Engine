/*
** EPITECH PROJECT, 2021
** indieStudio
** File description:
** ParticlesRenderer
*/

#ifdef __unix
    #define OS_Windows 0
#elif defined(_WIN32) || defined(WIN32)
    #define OS_Windows 1
#endif

#include "ParticlesRenderer.hpp"

IS::ParticlesRenderer::ParticlesRenderer()
{
}

IS::ParticlesRenderer::~ParticlesRenderer()
{
}

void IS::ParticlesRenderer::prepare(int scene, Camera3D camera)
{
    if (!OS_Windows) {
        for (auto it = _particles.begin(); it != _particles.end(); it++) {
            if (!it->update(camera))
                _particles.erase(it--);
        }
        std::sort(_particles.begin(), _particles.end());
    }
}

void IS::ParticlesRenderer::render(int scene, IS::Camera *camera)
{
    if (!OS_Windows) {
        Matrix viewMatrix = GetCameraMatrix(camera->getCamera3D());

        prepare(scene, camera->getCamera3D());
        for (Particle& particle : _particles) {
            updateModelViewMatrix(particle, viewMatrix);
            _particlesShader.loadData(
                particle.getTexOffset1(),
                particle.getTexOffset2(),
                particle.getTexturedModel().getNumberOfRows(),
                particle.getBlendFactor()
            );
            DrawModel(particle.getTexturedModel().getModel(), particle.getPosition(), particle.getScale(), WHITE);
        }
    }
}

void IS::ParticlesRenderer::updateModelViewMatrix(Particle &particle, Matrix viewMatrix)
{
    if (!particle.getTexturedModel().hasShader())
        particle.getTexturedModel().setShader(_particlesShader.getShader());
    Matrix matrix = particle.getTexturedModel().getModel().transform;
    
    matrix.m0 = viewMatrix.m0;
    matrix.m1 = viewMatrix.m4;
    matrix.m2 = viewMatrix.m8;
    matrix.m4 = viewMatrix.m1;
    matrix.m5 = viewMatrix.m5;
    matrix.m6 = viewMatrix.m9;
    matrix.m8 = viewMatrix.m2;
    matrix.m9 = viewMatrix.m6;
    matrix.m10 = viewMatrix.m10;
    particle.setModelTransform(matrix);
}

void IS::ParticlesRenderer::addParticles(const Particle &particle)
{
    if (!OS_Windows)
        _particles.push_back(particle);
}