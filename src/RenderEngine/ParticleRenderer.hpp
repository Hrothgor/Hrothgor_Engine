/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** ParticleRenderer
*/

#ifndef PARTICLERENDERER_HPP_
#define PARTICLERENDERER_HPP_

#include "Include.hpp"
#include "../Shader/ParticleShader.hpp"

namespace hr {
    class MainCamera3D;
    class Particle;

    class ParticleRenderer {
        public:
            ParticleRenderer();
            ~ParticleRenderer();

            void Start();
            void End();

            void BeginFrame();
            void Draw();
            void EndFrame();

            void RegisterParticle(Particle *particle);
        protected:
        private:
            std::vector<Particle *> _particles;
            ParticleShader _particleShader;
            MainCamera3D *_camera;
    };
}

#endif /* !PARTICLERENDERER_HPP_ */

