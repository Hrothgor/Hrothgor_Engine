/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** GameObject
*/

#ifndef GAMEOBJECT_HPP_
#define GAMEOBJECT_HPP_

#include "../include.hpp"
#include "Object.hpp"
#include "Component.hpp"

class GameObject : public Object {
    public:
        GameObject(GameObject *parent = nullptr);
        GameObject(const GameObject &parent = nullptr);
        ~GameObject();

        template <typename Comp>
        Comp *GetComponent()
        {
            auto it = _components.find(typeid(Comp));

            if (it == _components.end()) {
                std::cout << "Missing component : " + std::string(typeid(Comp).name()) << std::endl;
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
            auto it = _components.find(typeid(Comp));

            if (it == _components.end())
                return nullptr;
            return static_cast<Comp *>(it->second);
        }

        template <typename Comp>
        Comp *AddComponent()
        {
            auto it = _components.find(typeid(Comp));
            if (it != _components.end()) {
                std::cout << "2 components of the same type : " + std::string(typeid(Comp).name()) << std::endl;
                exit(84);
            }
            _components[typeid(Comp)] = new Comp(this);
            return _components[typeid(Comp)];
        }

        template <typename Comp>
        bool HasComponent()
        {
            return TryGetComponent<Comp>() != nullptr;
        }

        virtual void Start() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void End() override;

        Transform *GetTransform() const;
        GameObject *GetParent() const;
        std::unordered_map<std::type_index, Component *> GetComponents() const;

    protected:
    private:
        GameObject *_parent = nullptr;
        std::vector<GameObject *> _childs;
        std::unordered_map<std::type_index, Component *> _components;
        Transform *_transform = nullptr;
};

#endif /* !GAMEOBJECT_HPP_ */
