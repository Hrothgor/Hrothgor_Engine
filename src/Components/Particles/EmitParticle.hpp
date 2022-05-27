/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** EmitParticle
*/

#ifndef EMITPARTICLE_HPP_
#define EMITPARTICLE_HPP_

#include "Include.hpp"
#include "ParticleSystem.hpp"

namespace hr {
    class EmitParticle {
        public:
            static Vector3 CalcDirection(ParticleEmissionType type, Transform transform, float coneAngle);
        protected:
        private:
            static Vector3 CalcDirectionCone(Transform transform, float coneAngle);
            static Vector3 CalcDirectionSphere();
            static Vector3 CalcDirectionStatic();
    };
}

#endif /* !EMITPARTICLE_HPP_ */
