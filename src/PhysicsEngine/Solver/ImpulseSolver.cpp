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

            Vector3 angVelocityA = Vector3CrossProduct(aBody->GetAngularVelocity(), collision.points.A);
            Vector3 angVelocityB = Vector3CrossProduct(bBody->GetAngularVelocity(), collision.points.B);

            Vector3 fullVelocityA = Vector3Add(aBody->GetVelocity(), angVelocityA);
            Vector3 fullVelocityB = Vector3Add(bBody->GetVelocity(), angVelocityB);

            Vector3 contactVelocity = Vector3Subtract(fullVelocityB, fullVelocityA);

            float impulseForce = Vector3DotProduct(contactVelocity, collision.points.Normal);

            Vector3 inertiaA = Vector3CrossProduct(
                Vector3Multiply(Vector3One(), Vector3CrossProduct(collision.points.A, collision.points.Normal)), 
                collision.points.A
            ); // TODO InertiaTensor instead of Vector3One
            Vector3 inertiaB = Vector3CrossProduct(
                Vector3Multiply(Vector3One(), Vector3CrossProduct(collision.points.B, collision.points.Normal)), 
                collision.points.B
            ); // TODO InertiaTensor instead of Vector3One

            float angularEffect = Vector3DotProduct(Vector3Add(inertiaA, inertiaB), collision.points.Normal);

            float cRestitution = 0.66; // disperse some kinectic energy

            float j = (-(1 + cRestitution) * impulseForce) / (aBody->GetInvMass() + bBody->GetInvMass());
            Vector3 fullImpulse = Vector3Scale(collision.points.Normal, j);

            aBody->AddVelocity(Vector3Scale(fullImpulse, -1));
            bBody->AddVelocity(fullImpulse);

            aBody->AddAngularVelocity(Vector3CrossProduct(collision.points.A, Vector3Scale(fullImpulse, -1)));
            bBody->AddAngularVelocity(Vector3CrossProduct(collision.points.B, fullImpulse));
        }
    }
}

