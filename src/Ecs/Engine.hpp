/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** Engine
*/

#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include "../include.hpp"
#include "GameObject.hpp"

namespace hr {
    class Engine {
        public:
            Engine();
            ~Engine();

            void LoadScene();

            void Start();
            void Update();
            void End();

            template <typename Comp>
            Comp *FindObjectOfType()
            {
                for (auto ent : _entities) {
                    Comp *comp = ent->TryGetComponent<Comp>();
                    if (comp)
                        return comp;
                }
                return nullptr;
            }
            GameObject *Find(const std::string &name);
            GameObject *Instantiate(GameObject *object, GameObject *parent = nullptr);
            void Destroy(GameObject *object, float t = 0);

            void AddEntity(GameObject *object);
        private:
            std::vector<GameObject *> _entities;

        protected:
            static Engine *instance;
        public:
            Engine(Engine &other) = delete;
            void operator=(const Engine &) = delete;
            static Engine *Get() {
                if (instance == nullptr)
                    instance = new Engine();
                return instance;
            };
    };
}

#endif /* !ENGINE_HPP_ */
