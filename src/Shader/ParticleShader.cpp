/*
** EPITECH PROJECT, 2022
** Hrothgor_Engine
** File description:
** ParticleShader
*/

#include "ParticleShader.hpp"
#include "Components/Particles/Particle.hpp"

namespace hr {
    ParticleShader::ParticleShader()
        : DefaultShader("Engine/Ressources/Shaders/Particles.vs", "Engine/Ressources/Shaders/Particles.fs")
    {
        _locations = GetLocations();
    }

    ParticleShader::~ParticleShader()
    {
    }

    void ParticleShader::UpdateParticleLoc(Particle *particle)
    {
        float textoffset1[2] = {particle->GetTexOffset1().x, particle->GetTexOffset1().y};
        SetShaderValue(_shader, _locations[LOC_TEXTOFFSET1], &textoffset1, SHADER_UNIFORM_VEC2);

        float textoffset2[2] = {particle->GetTexOffset2().x, particle->GetTexOffset2().y};
        SetShaderValue(_shader, _locations[LOC_TEXTOFFSET2], &textoffset2, SHADER_UNIFORM_VEC2);

        float blend = particle->GetBlendFactor();
        SetShaderValue(_shader, _locations[LOC_BLEND], &blend, SHADER_UNIFORM_FLOAT);

        int numberOfRows = particle->GetNumberOfRows();
        SetShaderValue(_shader, _locations[LOC_NUMBEROFROWS], &numberOfRows, SHADER_UNIFORM_INT);
    }

    std::vector<int> ParticleShader::GetLocations() const
    {
        std::vector<int> locations(LOC_PARTICLE_SHADER_COUNT, 0);

        locations[LOC_TEXTOFFSET1] = GetShaderLocation(_shader, "texOffset1");
        locations[LOC_TEXTOFFSET2] = GetShaderLocation(_shader, "texOffset2");
        locations[LOC_BLEND] = GetShaderLocation(_shader, "blend");
        locations[LOC_NUMBEROFROWS] = GetShaderLocation(_shader, "numberOfRows");

        return locations;
    }
}