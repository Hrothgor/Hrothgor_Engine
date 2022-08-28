/*
** EPITECH PROJECT, 2022
** Hrothgor_Engine
** File description:
** Collider
*/

#ifndef COLLIDER_HPP_
#define COLLIDER_HPP_

#include "Include.hpp"
#include "Ecs/Component.hpp"

namespace hr {
    class Transform;
    class SphereCollider;
    class BoxCollider;
    class GameObject;

    struct CollisionPoints {
        Vector3 A;
        Vector3 B;
        Vector3 Normal;
        float Depth;
        bool HasCollision;
        bool Swap = false;
    };

    struct Collision {
        GameObject *objectA;
        GameObject *objectB;
        CollisionPoints points;
    };

    class Collider {
        public:
            virtual CollisionPoints TestCollision(
                const Transform *transform,
                const Collider *collider,
                const Transform *colliderTransform
            ) const = 0;

            virtual CollisionPoints TestCollision(
                const Transform *transform,
                const SphereCollider *sphere,
                const Transform *sphereTransform
            ) const = 0;

            virtual CollisionPoints TestCollision(
                const Transform *transform,
                const BoxCollider *box,
                const Transform *boxTransform
            ) const = 0;
        protected:
        private:
    };
}

#endif /* !COLLIDER_HPP_ */
