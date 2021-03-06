/*
** EPITECH PROJECT, 2022
** Hrothgor_Engine
** File description:
** SphereBox
*/


#include "PhysicsAlgo.hpp"
#include "Components/Transform.hpp"
#include "Components/Collider/BoxCollider.hpp"
#include "Components/Collider/SphereCollider.hpp"

#define CMP(x, y) \
	(fabsf(x - y) <= FLT_EPSILON * fmaxf(1.0f, fmaxf(fabsf(x), fabsf(y))))

namespace hr {
    Vector3 PhysicsAlgo::ClosestPoint(const BoxCollider *box, const Vector3 point) {
        Transform *transform = box->GetTransform();
        Vector3 result = transform->GetPositionWorld();
        Vector3 dir = point - result;

        std::vector<Vector3> localAxis = transform->GetLocalAxis();

        float size[3] = {box->GetSize().x, box->GetSize().y, box->GetSize().z};
        for (int i = 0; i < 3; i++) {
            Vector3 axis = Vector3Normalize(localAxis[i]);

            float distance = Vector3DotProduct(dir, axis);

            if (distance > size[i])
                distance = size[i];
            else if (distance < -size[i])
                distance = -size[i];

            result += axis * distance;
        }
        return result;
    }

    CollisionPoints PhysicsAlgo::FindSphereBoxCollisionPoints(
        const SphereCollider *a, const Transform *aTransform,
        const BoxCollider *b, const Transform *bTransform)
    {
        Vector3 A = aTransform->GetPositionWorld() + a->GetOffset();
        Vector3 B = bTransform->GetPositionWorld() + b->GetOffset();
        Vector3 closestPoint = ClosestPoint(b, A);

        Vector3 CPtoA = closestPoint - A;
        float distanceSqA = Vector3LengthSqr(CPtoA);
        if (distanceSqA > a->GetRadius() * a->GetRadius()) {
            return {Vector3Zero(), Vector3Zero(), Vector3Zero(), 0, false};
        }

        Vector3 CPtoB = closestPoint - B;
        float distanceSqB = Vector3LengthSqr(CPtoB);
        Vector3 normal; 
        if (CMP(distanceSqA, 0.0)) {
        	if (CMP(distanceSqB, 0.0)) {
                return {Vector3Zero(), Vector3Zero(), Vector3Zero(), 0, false};
        	}
        	normal = Vector3Normalize(CPtoB);
        }
        else {
        	normal = Vector3Normalize(A - closestPoint);
        }

        Vector3 outsidePoint = A - (normal * a->GetRadius());
        float distance = Vector3Length(closestPoint - outsidePoint);

        return {
            outsidePoint,
            closestPoint,
            normal * -1,
            distance,
            true
        };
    }
}
