/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** PhysicsAlgo
*/

#include "PhysicsAlgo.hpp"
#include "../Components/Transform.hpp"
#include "../Components/Collider/BoxCollider.hpp"
#include "../Components/Collider/SphereCollider.hpp"

namespace hr {
    CollisionPoints PhysicsAlgo::FindSphereSphereCollisionPoints(
        const SphereCollider *a, const Transform *aTransform,
        const SphereCollider *b, const Transform *bTransform)
    {
        Vector3 A = Vector3Add(aTransform->GetPosition(), a->GetOffset());
        Vector3 B = Vector3Add(bTransform->GetPosition(), b->GetOffset());

        Vector3 AtoB = Vector3Subtract(B, A);
        Vector3 BtoA = Vector3Subtract(A, B);

        if (Vector3Length(AtoB) > 2 * a->GetSphereRadius()
        || Vector3Length(BtoA) > 2 * b->GetSphereRadius())
            return {Vector3Zero(), Vector3Zero(), Vector3Zero(), 0, false};

        return {
            Vector3Add(A, Vector3Scale(Vector3Normalize(AtoB), a->GetSphereRadius())),
            Vector3Add(B, Vector3Scale(Vector3Normalize(BtoA), b->GetSphereRadius())),
            Vector3Normalize(AtoB),
            Vector3Length(AtoB),
            true
        };
    }

    CollisionPoints PhysicsAlgo::FindSphereBoxCollisionPoints(
        const SphereCollider *a, const Transform *aTransform,
        const BoxCollider *b, const Transform *bTransform)
    {
        CollisionPoints ret;

        (void)a;
        (void)aTransform;
        (void)b;
        (void)bTransform;
        return ret;
    }

    CollisionPoints PhysicsAlgo::FindBoxSphereCollisionPoints(
        const BoxCollider *a, const Transform *aTransform,
        const SphereCollider *b, const Transform *bTransform)
    {
        return FindSphereBoxCollisionPoints(b, bTransform, a, aTransform);
    }

    CollisionPoints PhysicsAlgo::FindBoxBoxCollisionPoints(
        const BoxCollider *a, const Transform *aTransform,
        const BoxCollider *b, const Transform *bTransform)
    {
        CollisionPoints ret;

        (void)a;
        (void)aTransform;
        (void)b;
        (void)bTransform;
        return ret;
    }
}


// ManifoldPoints FindSpherePlaneMaifoldPoints(
//     SphereCollider* a,
//     Transform* ta,
//     PlaneCollider* b,
//     Transform* tb)
// {
//     iw::vector3 A = a->Center + ta->Position;
//     iw::vector3 N = b->Plane.P.normalized() * tb->Rotation + tb->Position;
//     iw::vector3 P = N * b->Plane.D;

//     float d = (A - P).dot(N);

//     if (d > a->Radius) {
//         return { 0, 0, 0, true };
//     }

//     return {
//         A - N * a->Radius,
//         A - N * d,
//         -N.normalized(),
//         false
//     };
// }