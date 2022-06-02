/*
** EPITECH PROJECT, 2022
** Hrothgor_Engine
** File description:
** SphereSphere
*/

#include "PhysicsAlgo.hpp"
#include "../../Components/Transform.hpp"
#include "../../Components/Collider/BoxCollider.hpp"
#include "../../Components/Collider/SphereCollider.hpp"

namespace hr {
    CollisionPoints PhysicsAlgo::FindSphereSphereCollisionPoints(
        const SphereCollider *a, const Transform *aTransform,
        const SphereCollider *b, const Transform *bTransform)
    {
        Vector3 A = Vector3Add(aTransform->GetPositionWorld(), a->GetOffset());
        Vector3 B = Vector3Add(bTransform->GetPositionWorld(), b->GetOffset());

        Vector3 AtoB = Vector3Subtract(B, A);
        Vector3 BtoA = Vector3Subtract(A, B);

        if (Vector3Length(AtoB) > 2 * a->GetRadius()
        || Vector3Length(BtoA) > 2 * b->GetRadius())
            return {Vector3Zero(), Vector3Zero(), Vector3Zero(), 0, false};

        return {
            Vector3Add(A, Vector3Scale(Vector3Normalize(AtoB), a->GetRadius())),
            Vector3Add(B, Vector3Scale(Vector3Normalize(BtoA), b->GetRadius())),
            Vector3Normalize(BtoA),
            Vector3Length(AtoB),
            true
        };
    }
}
