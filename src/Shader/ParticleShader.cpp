/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** ParticleShader
*/

#include "ParticleShader.hpp"
#include "../Components/Particles/Particle.hpp"

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
        float elapsedTime = particle->GetElapsedTime();
        SetShaderValue(_shader, _locations[LOC_ELAPSEDTIME], &elapsedTime, SHADER_UNIFORM_FLOAT);

        float lifeLength = particle->GetLifeLength();
        SetShaderValue(_shader, _locations[LOC_LIFELENGTH], &lifeLength, SHADER_UNIFORM_FLOAT);

        int numberOfRows = particle->GetNumberOfRows();
        SetShaderValue(_shader, _locations[LOC_NUMBEROFROWS], &numberOfRows, SHADER_UNIFORM_INT);
    }

    std::vector<int> ParticleShader::GetLocations() const
    {
        std::vector<int> locations(LOC_PARTICLE_SHADER_COUNT, 0);

        locations[LOC_ELAPSEDTIME] = GetShaderLocation(_shader, "elapsedTime");
        locations[LOC_LIFELENGTH] = GetShaderLocation(_shader, "lifeLength");
        locations[LOC_NUMBEROFROWS] = GetShaderLocation(_shader, "numberOfRows");

        return locations;
    }
}