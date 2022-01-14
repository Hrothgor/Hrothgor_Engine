/*
** EPITECH PROJECT, 2021
** indieStudio
** File description:
** ParticlesRenderer
*/

#pragma once
#ifndef PARTICLESRENDERER_HPP_
#define PARTICLESRENDERER_HPP_

#include "../global.hpp"
#include "../Entities/Camera.hpp"
#include "../Particles/Particle.hpp"
#include "../Shaders/ParticlesShader.hpp"

namespace IS {
    class ParticlesRenderer {
        public:
            ParticlesRenderer();
            ~ParticlesRenderer();

            void prepare(int scene, Camera3D camera);
            void render(int scene, IS::Camera *camera);
            void updateModelViewMatrix(Particle &particle, Matrix viewMatrix);

            void addParticles(const Particle &particle);

        protected:
        private:
            ParticlesShader _particlesShader;

            std::vector<Particle> _particles;
    };
}

#endif /* !PARTICLESRENDERER_HPP_ */
