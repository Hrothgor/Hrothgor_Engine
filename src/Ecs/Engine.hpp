/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** Engine
*/

#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include "Include.hpp"
#include "GameObject.hpp"

namespace hr {
    class Engine {
        public:
            Engine();
            ~Engine();
            
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
            GameObject *Find(const UUIDv4::UUID &uuid);
            GameObject *Instantiate(GameObject *object, GameObject *parent = nullptr);
            void Destroy(GameObject *object, float t = 0);

            std::vector<GameObject *> GetEntities() const;
            std::vector<GameObject *> GetRootEntities() const;
            void ClearEntities();
            void AddEntity(GameObject *object);
            void RemoveEntity(GameObject *object);

            GameObject *GetSelectedEntity() const;
            void SetSelectedEntity(GameObject *object);

            GameObject *GetMainCamera() const;

            std::string GetProjectName() const;
            void SetProjectName(const std::string &projectName);

            void SetRunning(bool running);
            void SetSimulating(bool simulating);
        private:
            GameObject *_mainCamera;
            std::vector<GameObject *> _entities;
            GameObject *_selectedEntity = nullptr;

            std::string _projectName = "";

            bool _running = true;

            bool _simulating = false;
            std::vector<GameObject *> _savedEntities;
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
