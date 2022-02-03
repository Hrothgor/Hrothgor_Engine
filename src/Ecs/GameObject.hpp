/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** GameObject
*/

#ifndef GAMEOBJECT_HPP_
#define GAMEOBJECT_HPP_

#include "../include.hpp"
#include "Component.hpp"

namespace hr {
    class Transform;

    class GameObject : public Object {
        public:
            GameObject(GameObject *parent = nullptr);
            ~GameObject();

            template <typename Comp>
            Comp *GetComponent()
            {
                auto it = std::find_if(_components.begin(), _components.end(),
                    [&](const std::pair<std::type_index, Component *> &element){ return element.first == typeid(Comp);} );

                if (it == _components.end()) {
                    std::cout << _name + ": Can't get missing component : " + std::string(typeid(Comp).name()) << std::endl;
                    exit(84);
                }
                return static_cast<Comp *>(it->second);
            }

            template <typename Comp>
            Comp *GetComponentInChildren()
            {
                Comp *comp = TryGetComponent<Comp>();
                if (comp == nullptr) {
                    for (auto child : _childs) {
                        Comp *childComp = child->TryGetComponent<Comp>();
                        if (childComp != nullptr)
                            return childComp;
                    }
                }
                return comp;
            }

            template <typename Comp>
            Comp *TryGetComponent()
            {
                auto it = std::find_if(_components.begin(), _components.end(),
                    [&](const std::pair<std::type_index, Component *> &element){ return element.first == typeid(Comp);} );

                if (it == _components.end())
                    return nullptr;
                return static_cast<Comp *>(it->second);
            }

            template <typename Comp>
            Comp *AddComponent()
            {
                auto it = std::find_if(_components.begin(), _components.end(),
                    [&](const std::pair<std::type_index, Component *> &element){ return element.first == typeid(Comp);} );

                if (it != _components.end()) {
                    std::cout << _name + " has 2 components of the same type : " + std::string(typeid(Comp).name()) << std::endl;
                    exit(84);
                }
                Comp *newComp = new Comp(this);
                _components.push_back(std::make_pair<std::type_index, Component *>(typeid(Comp), newComp));
                return newComp;
            }

            template <typename Comp>
            void RemoveComponent()
            {
                auto it = std::find_if(_components.begin(), _components.end(),
                    [&](const std::pair<std::type_index, Component *> &element){ return element.first == typeid(Comp);} );
            
                if (it == _components.end()) {
                    std::cout << _name + ": Can't remove missing component : " + std::string(typeid(Comp).name()) << std::endl;
                    exit(84);
                }
                _components.erase(it);
            }

            template <typename Comp>
            bool HasComponent()
            {
                return TryGetComponent<Comp>() != nullptr;
            }

            template<typename Comp>
            bool HasComponentId(std::type_index typeId)
            {
                if (typeId == typeid(Comp))
                    return true;
                return false;
            }

            virtual void Start() override;
            virtual void Update() override;
            virtual void LateUpdate() override;
            virtual void End() override;

            Transform *GetTransform() const;
            GameObject *GetParent() const;
            std::vector<GameObject *> GetChilds() const;
            std::vector<std::pair<std::type_index, Component *>> GetComponents() const;
            void SetComponents(std::vector<std::pair<std::type_index, Component *>> components);

            void AddChild(GameObject *child);
            void RemoveChild(GameObject *child);

            void DetachFromParent();
            void SetParent(GameObject *parent);

            void Destroy();
        protected:
        private:
            GameObject *_parent = nullptr;
            std::vector<GameObject *> _childs;
            std::vector<std::pair<std::type_index, Component *>> _components;
            Transform *_transform = nullptr;

            bool ParentIsChild(GameObject *parent);
    };
}


#endif /* !GAMEOBJECT_HPP_ */
