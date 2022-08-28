/*
** EPITECH PROJECT, 2022
** Hrothgor_Engine
** File description:
** SmoothPositionSolver
*/

/*
** EPITECH PROJECT, 2022
** Hrothgor_Engine
** File description:
** SmoothPositionSolver
*/

#include "SmoothPositionSolver.hpp"
#include "Ecs/GameObject.hpp"
#include "Components/Transform.hpp"
#include "Components/RigidBody.hpp"

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

			float aInvMass = aBody->GetIsDynamic() ? aBody->GetInvMass() : 1.0;
			float bInvMass = bBody->GetIsDynamic() ? bBody->GetInvMass() : 1.0;

			const float percent = 0.8f;
			const float slop = 0.01f;

			Vector3 correction = collision.points.Normal * percent;
            correction *= fmax(collision.points.Depth - slop, 0.0f);
            correction *= 1.0f / (aInvMass + bInvMass);
		
			Vector3 deltaA = Vector3Zero();
			Vector3 deltaB = Vector3Zero();

			if (aBody->GetIsDynamic())
				deltaA = correction * aInvMass;

			if (bBody->GetIsDynamic())
				deltaB = correction * bInvMass;

			deltas.push_back(std::make_pair(deltaA, deltaB));
		}

		for (unsigned i = 0; i < collisions.size(); i++) {
            RigidBody *aBody = collisions[i].objectA->GetComponent<RigidBody>();
            RigidBody *bBody = collisions[i].objectB->GetComponent<RigidBody>();

			if (aBody->GetIsDynamic())
				collisions[i].objectA->GetTransform()->Translate((deltas[i].first * -1) * GetFrameTime());

			if (bBody->GetIsDynamic())
				collisions[i].objectB->GetTransform()->Translate(deltas[i].second * GetFrameTime());
		}
    }
}
