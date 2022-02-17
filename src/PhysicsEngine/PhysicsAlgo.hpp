/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** PhysicsAlgo
*/

#ifndef PHYSICSALGO_HPP_
#define PHYSICSALGO_HPP_

#include "include.hpp"
#include "../Components/Collider/Collider.hpp"

namespace hr {
    class PhysicsAlgo {
        public:
            static CollisionPoints FindSphereSphereCollisionPoints(
                const SphereCollider *a, const Transform *aTransform,
                const SphereCollider *b, const Transform *bTransform
            );

            static CollisionPoints FindSphereBoxCollisionPoints(
                const SphereCollider *a, const Transform *aTransform,
                const BoxCollider *b, const Transform *bTransform
            );

            static CollisionPoints FindBoxBoxCollisionPoints(
                const BoxCollider *a, const Transform *aTransform,
                const BoxCollider *b, const Transform *bTransform
            );
    };
}

#endif /* !PHYSICSALGO_HPP_ */
