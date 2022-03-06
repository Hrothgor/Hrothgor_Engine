/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** PhysicsWorld
*/

#include "PhysicsWorld.hpp"
#include "../Components/RigidBody.hpp"
#include "../Components/Transform.hpp"
#include "../Ecs/GameObject.hpp"
#include "../Components/Collider/Collider.hpp"
#include "../Components/Collider/SphereCollider.hpp"
#include "../Components/Collider/BoxCollider.hpp"

#include "Solver/SmoothPositionSolver.hpp"
#include "Solver/ImpulseSolver.hpp"

namespace hr {
    PhysicsWorld *PhysicsWorld::instance = nullptr;

    PhysicsWorld::PhysicsWorld()
    {
        AddSolver(new ImpulseSolver());
        AddSolver(new SmoothPositionSolver());
    }

    PhysicsWorld::~PhysicsWorld()
    {
    }

    void PhysicsWorld::Update()
    {
        ResolveCollision();

        for (GameObject *object : _objects) {
            Transform *tr = object->GetTransform();
            RigidBody *rb = object->GetComponent<RigidBody>();

            if (rb->GetUseGravity())
                rb->AddForce(Vector3Scale(_gravity, rb->GetMass()));

            rb->AddVelocity(Vector3Scale(rb->GetForce(), GetFrameTime()));

            tr->Rotate(rb->GetAngularVelocity()); // TODO : check if it's the right way to do it, i dont mult by delta time cause i mult by invTensor
            tr->Translate(Vector3Scale(rb->GetVelocity(), GetFrameTime()));

            rb->SetForce(Vector3Zero());
        }
        _objects.clear();
    }

    void PhysicsWorld::ResolveCollision()
    {
        std::vector<Collision> collisions;
        for (GameObject *a : _objects) {
            for (GameObject *b : _objects) {
                if (a == b) break;

                Collider *ca = TryGetCollider(a);
                Collider *cb = TryGetCollider(b);
                if (!ca || !cb)
                    continue;

                CollisionPoints points = ca->TestCollision(a->GetTransform(), cb, b->GetTransform());

                if (points.HasCollision) {
                    points.Swap ?
                        collisions.push_back({b, a, points}) :
                        collisions.push_back({a, b, points});
                }
            }
        }

        for (Solver *solver : _solvers)
            solver->Solve(collisions);
    }

    Collider *PhysicsWorld::TryGetCollider(GameObject *gameObject)
    {
        if (gameObject->TryGetComponent<SphereCollider>())
            return gameObject->GetComponent<SphereCollider>();
        if (gameObject->TryGetComponent<BoxCollider>())
            return gameObject->GetComponent<BoxCollider>();
        return nullptr;
    }

    void PhysicsWorld::RegisterObject(GameObject *object)
    {
        _objects.push_back(object);
    }

    void PhysicsWorld::AddSolver(Solver *solver)
    {
        _solvers.push_back(solver);
    }
}