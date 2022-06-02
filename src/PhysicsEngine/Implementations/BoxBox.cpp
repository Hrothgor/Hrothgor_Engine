/*
** EPITECH PROJECT, 2022
** Hrothgor_Engine
** File description:
** BoxBox
*/

#include "PhysicsAlgo.hpp"
#include "Components/Transform.hpp"
#include "Components/Collider/BoxCollider.hpp"
#include "Components/Collider/SphereCollider.hpp"

#include "Ecs/GameObject.hpp"
#include "Components/MeshRenderer.hpp"

namespace hr {
    bool PhysicsAlgo::GetSeparatingPlane(
        const Vector3& relativePos, const Vector3& Plane, 
        const std::vector<Vector3>& aAxis, const Vector3& aSize,
        const std::vector<Vector3>& bAxis, const Vector3& bSize)
    {
        return (fabs(Vector3DotProduct(relativePos, Plane)) > 

            (fabs(Vector3DotProduct((aAxis[0] * aSize.x), Plane)) +
            fabs(Vector3DotProduct((aAxis[1] * aSize.y), Plane)) +
            fabs(Vector3DotProduct((aAxis[2] * aSize.z), Plane)) +

            fabs(Vector3DotProduct((bAxis[0] * bSize.x), Plane)) + 
            fabs(Vector3DotProduct((bAxis[1] * bSize.y), Plane)) +
            fabs(Vector3DotProduct((bAxis[2] * bSize.z), Plane))));
    }

    CollisionPoints PhysicsAlgo::FindBoxBoxCollisionPoints(
        const BoxCollider *a, const Transform *aTransform,
        const BoxCollider *b, const Transform *bTransform)
    {
        Vector3 A = aTransform->GetPositionWorld() + a->GetOffset();
        Vector3 B = bTransform->GetPositionWorld() + b->GetOffset();
        std::vector<Vector3> aAxis = aTransform->GetLocalAxis();
        std::vector<Vector3> bAxis = bTransform->GetLocalAxis();
        Vector3 aSize = a->GetSize();
        Vector3 bSize = b->GetSize();

        Vector3 rPos = B - A; // peut etre static

        bool colliding = !(
            GetSeparatingPlane(rPos, aAxis[0], aAxis, aSize, bAxis, bSize) ||
            GetSeparatingPlane(rPos, aAxis[1], aAxis, aSize, bAxis, bSize) ||
            GetSeparatingPlane(rPos, aAxis[2], aAxis, aSize, bAxis, bSize) ||
            GetSeparatingPlane(rPos, bAxis[0], aAxis, aSize, bAxis, bSize) ||
            GetSeparatingPlane(rPos, bAxis[1], aAxis, aSize, bAxis, bSize) ||
            GetSeparatingPlane(rPos, bAxis[2], aAxis, aSize, bAxis, bSize) ||
            GetSeparatingPlane(rPos, Vector3CrossProduct(aAxis[0], bAxis[0]), aAxis, aSize, bAxis, bSize) ||
            GetSeparatingPlane(rPos, Vector3CrossProduct(aAxis[0], bAxis[1]), aAxis, aSize, bAxis, bSize) ||
            GetSeparatingPlane(rPos, Vector3CrossProduct(aAxis[0], bAxis[2]), aAxis, aSize, bAxis, bSize) ||
            GetSeparatingPlane(rPos, Vector3CrossProduct(aAxis[1], bAxis[0]), aAxis, aSize, bAxis, bSize) ||
            GetSeparatingPlane(rPos, Vector3CrossProduct(aAxis[1], bAxis[1]), aAxis, aSize, bAxis, bSize) ||
            GetSeparatingPlane(rPos, Vector3CrossProduct(aAxis[1], bAxis[2]), aAxis, aSize, bAxis, bSize) ||
            GetSeparatingPlane(rPos, Vector3CrossProduct(aAxis[2], bAxis[0]), aAxis, aSize, bAxis, bSize) ||
            GetSeparatingPlane(rPos, Vector3CrossProduct(aAxis[2], bAxis[1]), aAxis, aSize, bAxis, bSize) ||
            GetSeparatingPlane(rPos, Vector3CrossProduct(aAxis[2], bAxis[2]), aAxis, aSize, bAxis, bSize)
        );

        if (colliding)
            aTransform->GetGameObject()->GetComponent<MeshRenderer>()->SetColor(RED);
        else
            aTransform->GetGameObject()->GetComponent<MeshRenderer>()->SetColor(WHITE);

        return {
            Vector3Zero(),
            Vector3Zero(),
            Vector3Zero(),
            0,
            colliding
        };
    }
}