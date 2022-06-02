/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** ImpulseSolver
*/

#include "ImpulseSolver.hpp"
#include "Ecs/GameObject.hpp"
#include "Components/Transform.hpp"
#include "Components/RigidBody.hpp"

namespace hr {
    ImpulseSolver::ImpulseSolver()
    {
    }

    ImpulseSolver::~ImpulseSolver()
    {
    }

    void ImpulseSolver::Solve(std::vector<Collision> &collisions)
    {
		for (Collision &collision : collisions) {
            RigidBody *aBody = collision.objectA->GetComponent<RigidBody>();
            RigidBody *bBody = collision.objectB->GetComponent<RigidBody>();

            Vector3 aVel = aBody->GetIsDynamic() ? aBody->GetVelocity() : Vector3Zero();
            Vector3 bVel = bBody->GetIsDynamic() ? bBody->GetVelocity() : Vector3Zero();
            Vector3 rVel = bVel - aVel;
            float impulseForce = Vector3DotProduct(rVel, collision.points.Normal);

            float aInvMass = aBody->GetIsDynamic() ? aBody->GetInvMass() : 1.0;
            float bInvMass = bBody->GetIsDynamic() ? bBody->GetInvMass() : 1.0;

            // Vector3 angVelocityA = Vector3CrossProduct(aBody->GetAngularVelocity(), collision.points.A);
            // Vector3 angVelocityB = Vector3CrossProduct(bBody->GetAngularVelocity(), collision.points.B);

            // Vector3 fullVelocityA = aBody->GetVelocity() + angVelocityA;
            // Vector3 fullVelocityB = bBody->GetVelocity() + angVelocityB;

            // Vector3 contactVelocity = fullVelocityB - fullVelocityA;

            // float impulseForce = Vector3DotProduct(contactVelocity, collision.points.Normal);
            if (impulseForce >= 0)
                continue;

            float Restitution = 0.66; // disperse some kinectic energy

            float e = (aBody->GetIsDynamic() ? Restitution : 1) * (bBody->GetIsDynamic() ? Restitution : 1);

            // Vector3 inertiaA = Vector3CrossProduct(
            //     Vector3Multiply(Vector3One(), Vector3CrossProduct(collision.points.A, collision.points.Normal)), 
            //     collision.points.A
            // ); // TODO InertiaTensor instead of Vector3One
            // Vector3 inertiaB = Vector3CrossProduct(
            //     Vector3Multiply(Vector3One(), Vector3CrossProduct(collision.points.B, collision.points.Normal)), 
            //     collision.points.B
            // ); // TODO InertiaTensor instead of Vector3One

            // float angularEffect = Vector3DotProduct(inertiaA + inertiaB, collision.points.Normal);
            // float j = (-(1 + Restitution) * impulseForce) / (aBody->GetInvMass() + bBody->GetInvMass());

            float j = (-(1 + e) * impulseForce) / (aInvMass + bInvMass);

            Vector3 fullImpulse = collision.points.Normal * j;

            if (aBody->GetIsDynamic()) {
                aBody->AddVelocity(fullImpulse * -1);

                Vector3 centerOfMass = aBody->GetTransform()->GetPositionWorld();
                Vector3 torque = Vector3CrossProduct(collision.points.A - centerOfMass, fullImpulse);
                aBody->SetAngularVelocity(Vector3Zero());
                aBody->AddAngularVelocity(torque);
                // aBody->AddAngularVelocity(Vector3CrossProduct(collision.points.A, fullImpulse));
            }

            if (bBody->GetIsDynamic()) {
                bBody->AddVelocity(fullImpulse);

                Vector3 centerOfMass = bBody->GetTransform()->GetPositionWorld();
                Vector3 torque = Vector3CrossProduct(collision.points.B - centerOfMass, fullImpulse);
                bBody->SetAngularVelocity(Vector3Zero());
                bBody->AddAngularVelocity(torque);
                // bBody->AddAngularVelocity(Vector3CrossProduct(collision.points.B, fullImpulse * -1));
            }
            
            // friction


            aVel = aBody->GetIsDynamic() ? aBody->GetVelocity() : Vector3Zero();
            bVel = bBody->GetIsDynamic() ? bBody->GetVelocity() : Vector3Zero();
            rVel = bVel - aVel;
            impulseForce = Vector3DotProduct(rVel, collision.points.Normal);

            Vector3 tangent = rVel - (collision.points.Normal * impulseForce);


            if (Vector3Length(tangent) > 0.0001) { // safe normalize
				tangent = Vector3Normalize(tangent);
			}

            float fVel = Vector3DotProduct(tangent, collision.points.Normal);

            float aSF = aBody ? aBody->GetStaticFriction()  : 0;
			float bSF = bBody ? bBody->GetStaticFriction()  : 0;
			float aDF = aBody ? aBody->GetDynamicFriction() : 0;
			float bDF = bBody ? bBody->GetDynamicFriction() : 0;
            float mu = Vector2Length({aSF, bSF});

            float f = -fVel / (aInvMass + bInvMass);

            Vector3 friction;
            if (abs(f) < j * mu) {
				friction = tangent * f;
			} else {
                mu = Vector2Length({aDF, bDF});
                friction = tangent * -j * mu;
			}

			if (aBody->GetIsDynamic())
				aBody->AddVelocity(friction * -1);

			if (bBody->GetIsDynamic())
				bBody->AddVelocity(friction);
        }
    }
}
