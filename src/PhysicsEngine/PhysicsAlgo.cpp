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

    CollisionPoints PhysicsAlgo::FindSphereBoxCollisionPoints(
        const SphereCollider *a, const Transform *aTransform,
        const BoxCollider *b, const Transform *bTransform)
    {
        // TODO STILL BUGGY
        Vector3 A = Vector3Add(aTransform->GetPositionWorld(), a->GetOffset());
        Vector3 B = Vector3Add(bTransform->GetPositionWorld(), b->GetOffset());
        Vector3 closestPoint = ClosestPoint(b, A);

        Vector3 CPtoA = Vector3Subtract(closestPoint, A);
        float distanceSqA = Vector3LengthSqr(CPtoA);
        if (distanceSqA > a->GetRadius() * a->GetRadius()) {
            return {Vector3Zero(), Vector3Zero(), Vector3Zero(), 0, false};
        }

        Vector3 CPtoB = Vector3Subtract(closestPoint, B);
        float distanceSqB = Vector3LengthSqr(CPtoB);
        Vector3 normal; 
        if (CMP(distanceSqA, 0.0)) {
        	if (CMP(distanceSqB, 0.0)) {
                return {Vector3Zero(), Vector3Zero(), Vector3Zero(), 0, false};
        	}
        	normal = Vector3Normalize(CPtoB);
        }
        else {
        	normal = Vector3Normalize(Vector3Subtract(A, closestPoint));
        }

        Vector3 outsidePoint = Vector3Subtract(A, Vector3Scale(normal, a->GetRadius()));

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
        std::vector<float> normals;
        for (auto normal : normals) {
            
        }
        // foreach normal in allNormals
        // {
        // 	//projection might be a for loop over one model’s vertices simply getting max and min value of dot(vertex, normal)
        // 	intervalA = projection(objectA, normal);
        // 	intervalB = projection(objectB, normal);
            
        // 	//from this point on take first object as moving and the second one as static
        // 	//calculate the velocity of moving object
        // 	finalVelocity = velocityA-velocityB;

        // 	//in order to prevent tunneling we need to expand the intervals by the model velocities - optimization
        // 	//if the velocity is > 0 then we expand it to the right and vice versa
        // 	if (finalVelocity > 0.0f)
        // 	    velocityIntervalA.end += intervalA.end + finalVelocity;
        // 	else
        // 	    velocityIntervalA.start += intervalB.start + finalVelocity;

        // 	//if the velocity expanded intervals overlap, test the times
        // 	if (velocityIntervalA.start <= intervalB.end && intervalB.start <= velocityIntervalA.end)
        // 	{
	    //we need the time intervals of overlap and find out if they overlap with each other :D
	    //we have multiple time intervals, let's take the latest entry time and the earliest leave time, if maxEntry collision

	    //it's calculated for one frame and since the velocity says how much the object moves in one frame, max time is 1 min is 0
        //     entry = 0.0f;
        //     leave = 1.0f;
        //     amount = 0.0;

        //     if (intervalA.end <= intervalB.start)
        //     {
        // 	//interval A is going away from interval B, no possible collision
        // 	if (finalVelocity <= 0.0f)
        // 	    return res;
        // 	//calculate the time of entering and leaving the other interval, t=s/v
        // 	entry = absVal((intervalB.start - intervalA.end)/finalVelocity);
        // 	leave = absVal((intervalB.end - intervalA.start)/finalVelocity);
        //     }
        //     //interval B is on the left
        //     else if (intervalB.end <= intervalA.start)
        //     {
        // 	if (finalVelocity >=0.0f)
        // 	    return res;
        // 	entry = absVal((intervalA.start - intervalB.end)/finalVelocity);
        // 	leave = absVal((intervalA.end - intervalB.start)/finalVelocity);
        //     }
        //     //intervals already overlap
        //     else
        //     {
        // 	//deciding how do the overlap
        // 	if (intervalA.start <= intervalB.start)
        // 	{
        // 	    leave = absVal((intervalB.end - intervalA.start)/finalVelocity);
        // 	    amount = intervalA.end - intervalB.start;
        // 	}
        // 	else
        // 	{
        // 	    leave = absVal((intervalA.end - intervalB.start)/finalVelocity);
        // 	    amount = intervalB.end - intervalA.start;
        // 	}
        //     }

        //     //here we can leave if the collision happens in the future frames (time is higher than max time of the frame = 1)
        //     if (entry > 1.0f)
        // 	return;

        
        //     //save max and min of overlap borders
        //     if (maxEntry < entry)
        //     {
        // 	maxEntry = entry;
        // 	minAmout = amount;
        // 	collisionNormal = normal;
        //     }
        //   	    //this is the case of overlap, we can use the amount to push the objects out of each other
        //     else if (amount < minAmount)
        //     {
        // 	minAmount = amount;
        // 	overlapNormal = normal;
        //     }
        //     if (minLeave >= leave)
        // 	minLeave = leave;

        // }
        // //if they don't overlap then we have found the separating axis (current normal) and we can say there is no collision
        // else
        //     return;
        // }

        // //if there is a time interval that lies inside all the found ones, collision happened
        // if (minLeave>=maxEntry)
        //     foundInterval = true;

        (void)a;
        (void)aTransform;
        (void)b;
        (void)bTransform;
        return {Vector3Zero(), Vector3Zero(), Vector3Zero(), 0, false};
    }

    Vector3 PhysicsAlgo::ClosestPoint(const BoxCollider *box, const Vector3 point) {
        Transform *transform = box->GetTransform();
        Vector3 result = transform->GetPositionWorld();
        Vector3 dir = Vector3Subtract(point, result);


        Vector3 rotation = transform->GetRotation();
        Matrix rotationMatrix = MatrixRotateXYZ({DEG2RAD * rotation.x, DEG2RAD * rotation.y, DEG2RAD * rotation.z});
        float16 rotationMatrixPtr = MatrixToFloatV(rotationMatrix);

        float size[3] = {box->GetSize().x, box->GetSize().y, box->GetSize().z};
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
}