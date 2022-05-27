/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** PhysicsWorld
*/

#ifndef PHYSICSWORLD_HPP_
#define PHYSICSWORLD_HPP_

#include "Include.hpp"

namespace hr {
    struct Collision;
    class Collider;
    class GameObject;
    class Solver;

    class PhysicsWorld {
        public:
            PhysicsWorld();
            ~PhysicsWorld();

            void Update();
            void ResolveCollision();

            Collider *TryGetCollider(GameObject *gameObject);

            void RegisterObject(GameObject *model);
            void AddSolver(Solver *solver);

        protected:
        private:
            std::vector<GameObject *> _objects;
            std::vector<Solver *> _solvers;
            Vector3 _gravity = {0, -9.81, 0};

        protected:
            static PhysicsWorld *instance;
        public:
            PhysicsWorld(PhysicsWorld &other) = delete;
            void operator=(const PhysicsWorld &) = delete;
            static PhysicsWorld *Get() {
                if (instance == nullptr)
                    instance = new PhysicsWorld();
                return instance;
            };
    };
}

#endif /* !PHYSICSWORLD_HPP_ */
