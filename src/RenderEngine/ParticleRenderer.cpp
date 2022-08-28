/*
** EPITECH PROJECT, 2022
** Hrothgor_Engine
** File description:
** ParticleRenderer
*/

#include "ParticleRenderer.hpp"
#include "Ecs/Engine.hpp"

#include "Components/Transform.hpp"
#include "Components/Particles/Particle.hpp"
#include "Components/Particles/ParticleSystem.hpp"
#include "Components/MainCamera3D.hpp"

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
        Material material = LoadMaterialDefault();
        for (Particle *particle : _particles) {
            BeginBlendMode(particle->GetParentSystem()->GetBlendMode());
            material.maps[MATERIAL_MAP_ALBEDO].texture = particle->GetTexture();
            material.maps[MATERIAL_MAP_ALBEDO].color = particle->GetStartColor();
            if (particle->GetTextureType() == ATLAS) {
                material.shader = _particleShader.GetShader();
                _particleShader.UpdateParticleLoc(particle);
            } else {
                material.shader.id = rlGetShaderIdDefault();
            }
            Matrix transform = particle->GetTransform().GetTransformMatrix();
            transform = MatrixMultiply(particle->GetBillboardMatrix(), transform);
            DrawMesh(particle->GetMesh(), material, transform);
        }
        RL_FREE(material.maps);
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
        UnloadShader(_particleShader.GetShader());
    }
}

