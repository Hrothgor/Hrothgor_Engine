/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** ParticleRenderer
*/

#include "ParticleRenderer.hpp"
#include "../Ecs/Engine.hpp"

#include "../Components/Transform.hpp"
#include "../Components/Particles/Particle.hpp"
#include "../Components/MainCamera3D.hpp"

namespace hr {
    ParticleRenderer::ParticleRenderer()
    {
    }

    ParticleRenderer::~ParticleRenderer()
    {
    }

    void ParticleRenderer::Start()
    {
        _camera = Engine::Get()->GetMainCamera()->GetComponent<MainCamera3D>();
    }

    void ParticleRenderer::BeginFrame()
    {
        rlDisableDepthMask();
        BeginBlendMode(BLEND_ADDITIVE);

        std::vector<Particle *> particles;
        for (auto part : _particles)
            if (part->Update(_camera->GetCamera3D()))
                particles.push_back(part);
        std::sort(particles.begin(), particles.end());
        _particles.clear();
        _particles = particles;
    }

    void ParticleRenderer::Draw()
    {
        BeginFrame();
        for (Particle *particle : _particles) {
            Material material = LoadMaterialDefault();
            material.maps[MATERIAL_MAP_ALBEDO].texture = particle->GetTexture();
            material.maps[MATERIAL_MAP_ALBEDO].color = particle->GetStartColor();
            Matrix transform = particle->GetTransform().GetTransformMatrix();
            transform = MatrixMultiply(particle->GetBillboardMatrix(), transform);
            DrawMesh(particle->GetMesh(), material, transform);
        }
        EndFrame();
    }

    void ParticleRenderer::EndFrame()
    {
        EndBlendMode();
        rlEnableDepthMask();
    }

    void ParticleRenderer::RegisterParticle(Particle *particle)
    {
        _particles.push_back(particle);
    }

    void ParticleRenderer::End()
    {

    }
}

