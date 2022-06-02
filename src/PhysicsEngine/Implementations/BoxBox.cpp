/*
** EPITECH PROJECT, 2022
** Hrothgor_Engine
** File description:
** BoxBox
*/

#include "PhysicsAlgo.hpp"
#include "../../Components/Transform.hpp"
#include "../../Components/Collider/BoxCollider.hpp"
#include "../../Components/Collider/SphereCollider.hpp"

namespace hr {
    CollisionPoints PhysicsAlgo::FindBoxBoxCollisionPoints(
        const BoxCollider *a, const Transform *aTransform,
        const BoxCollider *b, const Transform *bTransform)
    {
        (void)a;
        (void)aTransform;
        (void)b;
        (void)bTransform;
        return {Vector3Zero(), Vector3Zero(), Vector3Zero(), 0, false};
    }
}