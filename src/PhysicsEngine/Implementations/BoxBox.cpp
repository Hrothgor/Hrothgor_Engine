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

namespace hr {
    bool PhysicsAlgo::GetSeparatingPlane(
        const Vector3& relativePos, const Vector3& Plane, 
        const std::vector<Vector3>& aAxis, const Vector3& aSize,
        const std::vector<Vector3>& bAxis, const Vector3& bSize)
    {
        float aProj = fabs(Vector3DotProduct((aAxis[0] * aSize.x), Plane)) +
                    fabs(Vector3DotProduct((aAxis[1] * aSize.y), Plane)) +
                    fabs(Vector3DotProduct((aAxis[2] * aSize.z), Plane));

        float bProj = fabs(Vector3DotProduct((bAxis[0] * bSize.x), Plane)) + 
                    fabs(Vector3DotProduct((bAxis[1] * bSize.y), Plane)) +
                    fabs(Vector3DotProduct((bAxis[2] * bSize.z), Plane));
        
        float rProj = fabs(Vector3DotProduct(relativePos, Plane));

        if (rProj > aProj + bProj)
            return true;
        return false;
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

        Vector3 rPos = B - A;

        // si 1 separatingPlane true pas de collision
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

        return {
            Vector3Zero(),
            Vector3Zero(),
            Vector3Zero(),
            0,
            colliding
        };
    }
}