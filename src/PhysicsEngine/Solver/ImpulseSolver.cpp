/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** ImpulseSolver
*/

#include "ImpulseSolver.hpp"
#include "../../Ecs/GameObject.hpp"
#include "../../Components/Transform.hpp"
#include "../../Components/RigidBody.hpp"

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
            Vector3 rVel = Vector3Subtract(bVel, aVel);
            float impulseForce = Vector3DotProduct(rVel, collision.points.Normal);

            float aInvMass = aBody->GetIsDynamic() ? aBody->GetInvMass() : 1.0;
            float bInvMass = bBody->GetIsDynamic() ? bBody->GetInvMass() : 1.0;

            // Vector3 angVelocityA = Vector3CrossProduct(aBody->GetAngularVelocity(), collision.points.A);
            // Vector3 angVelocityB = Vector3CrossProduct(bBody->GetAngularVelocity(), collision.points.B);

            // Vector3 fullVelocityA = Vector3Add(aBody->GetVelocity(), angVelocityA);
            // Vector3 fullVelocityB = Vector3Add(bBody->GetVelocity(), angVelocityB);

            // Vector3 contactVelocity = Vector3Subtract(fullVelocityB, fullVelocityA);

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

            // float angularEffect = Vector3DotProduct(Vector3Add(inertiaA, inertiaB), collision.points.Normal);
            // float j = (-(1 + Restitution) * impulseForce) / (aBody->GetInvMass() + bBody->GetInvMass());

            float j = (-(1 + e) * impulseForce) / (aInvMass + bInvMass);

            Vector3 fullImpulse = Vector3Scale(collision.points.Normal, j);

            if (aBody->GetIsDynamic()) {
                aBody->AddVelocity(Vector3Scale(fullImpulse, -1));
                aBody->AddAngularVelocity(Vector3CrossProduct(collision.points.A, fullImpulse));
            }

            if (bBody->GetIsDynamic()) {
                bBody->AddVelocity(fullImpulse);
                bBody->AddAngularVelocity(Vector3CrossProduct(collision.points.B, Vector3Scale(fullImpulse, -1)));
            }
            
            // friction to add
            // aVel = aBody->GetIsDynamic() ? aBody->GetVelocity() : Vector3Zero();
            // bVel = bBody->GetIsDynamic() ? bBody->GetVelocity() : Vector3Zero();
            // rVel = Vector3Subtract(bVel, aVel);
            // impulseForce = Vector3DotProduct(rVel, collision.points.Normal);
        }
    }
}
