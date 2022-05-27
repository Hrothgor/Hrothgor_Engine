/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** ParticleShader
*/

#ifndef PARTICLESHADER_HPP_
#define PARTICLESHADER_HPP_

#include "Include.hpp"
#include "DefaultShader.hpp"

namespace hr {
    class Particle;

    enum ParticleShaderLoc {
        LOC_ELAPSEDTIME = 0,
        LOC_LIFELENGTH,
        LOC_NUMBEROFROWS,
        LOC_PARTICLE_SHADER_COUNT
    };

    class ParticleShader : public DefaultShader {
        public:
            ParticleShader();
            ~ParticleShader();

            void UpdateParticleLoc(Particle *particle);

            std::vector<int> GetLocations() const;
        protected:
        private:
            std::vector<int> _locations;
    };
}

#endif /* !PARTICLESHADER_HPP_ */
