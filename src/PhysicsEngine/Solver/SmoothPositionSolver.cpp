/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** SmoothPositionSolver
*/

#include "SmoothPositionSolver.hpp"
#include "../../Ecs/GameObject.hpp"
#include "../../Components/Transform.hpp"
#include "../../Components/RigidBody.hpp"

namespace hr {
    SmoothPositionSolver::SmoothPositionSolver()
    {
    }

    SmoothPositionSolver::~SmoothPositionSolver()
    {
    }

    void SmoothPositionSolver::Solve(std::vector<Collision> &collisions)
    {
        std::vector<std::pair<Vector3, Vector3>> deltas;

		for (Collision &collision : collisions) {
            RigidBody *aBody = collision.objectA->GetComponent<RigidBody>();
            RigidBody *bBody = collision.objectB->GetComponent<RigidBody>();

			float aInvMass = aBody->GetIsDynamic() ? 1 / aBody->GetMass() : 0.0;
			float bInvMass = bBody->GetIsDynamic() ? 1 / bBody->GetMass() : 0.0;

			const float percent = 0.8f;
			const float slop = 0.01f;

			Vector3 correction = Vector3Scale(collision.points.Normal, percent);
            correction = Vector3Scale(correction, fmax(collision.points.Depth - slop, 0.0f));
            correction = Vector3Scale(correction, 1.0f / (aInvMass + bInvMass));
		
			Vector3 deltaA;
			Vector3 deltaB;

			if (aBody->GetIsDynamic())
				deltaA = Vector3Scale(correction, aInvMass);

			if (bBody->GetIsDynamic())
				deltaB = Vector3Scale(correction, bInvMass);

			deltas.push_back(std::make_pair(deltaA, deltaB));
		}

		for (unsigned i = 0; i < collisions.size(); i++) {
            RigidBody *aBody = collisions[i].objectA->GetComponent<RigidBody>();
            RigidBody *bBody = collisions[i].objectB->GetComponent<RigidBody>();

			if (aBody->GetIsDynamic())
				collisions[i].objectA->GetTransform()->Translate(Vector3Scale(Vector3Scale(deltas[i].first, -1), GetFrameTime()));

			if (bBody->GetIsDynamic())
				collisions[i].objectB->GetTransform()->Translate(Vector3Scale(deltas[i].second, GetFrameTime()));
		}
    }
}
