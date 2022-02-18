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

#define CMP(x, y) \
	(fabsf(x - y) <= FLT_EPSILON * fmaxf(1.0f, fmaxf(fabsf(x), fabsf(y))))

namespace hr {
    Vector3 PhysicsAlgo::ClosestPoint(const BoxCollider *box, const Vector3 point) {
        Transform *transform = box->GetTransform();
        Vector3 result = transform->GetPositionWorld();
        Vector3 dir = Vector3Subtract(point, result);


        Vector3 rotation = transform->GetRotation();
        Matrix rotationMatrix = MatrixRotateXYZ({DEG2RAD * rotation.x, DEG2RAD * rotation.y, DEG2RAD * rotation.z});
        float16 rotationMatrixPtr = MatrixToFloatV(rotationMatrix);

        float size[3] = {box->GetCubeWidth() / 2, box->GetCubeHeight() / 2, box->GetCubeLength() / 2};
        for (int i = 0; i < 3; i++) {
            Vector3 axis = {rotationMatrixPtr.v[i], rotationMatrixPtr.v[i + 4], rotationMatrixPtr.v[i + 8]};
            axis = Vector3Normalize(axis);

            float distance = Vector3DotProduct(dir, axis);

            if (distance > size[i])
                distance = size[i];
            else if (distance < -size[i])
                distance = -size[i];

            result = Vector3Add(result, Vector3Scale(axis, distance));
        }
        return result;
    }

    CollisionPoints PhysicsAlgo::FindSphereSphereCollisionPoints(
        const SphereCollider *a, const Transform *aTransform,
        const SphereCollider *b, const Transform *bTransform)
    {
        Vector3 A = Vector3Add(aTransform->GetPositionWorld(), a->GetOffset());
        Vector3 B = Vector3Add(bTransform->GetPositionWorld(), b->GetOffset());

        Vector3 AtoB = Vector3Subtract(B, A);
        Vector3 BtoA = Vector3Subtract(A, B);

        if (Vector3Length(AtoB) > 2 * a->GetSphereRadius()
        || Vector3Length(BtoA) > 2 * b->GetSphereRadius())
            return {Vector3Zero(), Vector3Zero(), Vector3Zero(), 0, false};

        return {
            Vector3Add(A, Vector3Scale(Vector3Normalize(AtoB), a->GetSphereRadius())),
            Vector3Add(B, Vector3Scale(Vector3Normalize(BtoA), b->GetSphereRadius())),
            Vector3Normalize(BtoA),
            Vector3Length(AtoB),
            true
        };
    }

    CollisionPoints PhysicsAlgo::FindSphereBoxCollisionPoints(
        const SphereCollider *a, const Transform *aTransform,
        const BoxCollider *b, const Transform *bTransform)
    {
        Vector3 closestPoint = ClosestPoint(b, aTransform->GetPositionWorld());

        Vector3 CPtoA = Vector3Subtract(closestPoint, aTransform->GetPositionWorld());
        float distanceSqA = Vector3LengthSqr(CPtoA);
        if (distanceSqA > a->GetSphereRadius() * a->GetSphereRadius()) {
            return {Vector3Zero(), Vector3Zero(), Vector3Zero(), 0, false};
        }

        Vector3 CPtoB = Vector3Subtract(closestPoint, bTransform->GetPositionWorld());
        float distanceSqB = Vector3LengthSqr(CPtoB);
        Vector3 normal; 
        if (CMP(distanceSqA, 0.0)) {
        	if (CMP(distanceSqB, 0.0)) {
                return {Vector3Zero(), Vector3Zero(), Vector3Zero(), 0, false};
        	}
        	normal = Vector3Normalize(CPtoB);
        }
        else {
        	normal = Vector3Normalize(Vector3Subtract(aTransform->GetPositionWorld(), closestPoint));
        }

        Vector3 outsidePoint = Vector3Subtract(aTransform->GetPositionWorld(), Vector3Scale(normal, a->GetSphereRadius()));

        float distance = Vector3Length(Vector3Subtract(closestPoint, outsidePoint));

        return {
            outsidePoint,
            closestPoint,
            Vector3Scale(normal, -1),
            distance,
            true
        };
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