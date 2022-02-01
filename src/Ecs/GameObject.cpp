/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** GameObject
*/

#include "GameObject.hpp"
#include "../Components/Transform.hpp"
#include "Engine.hpp"

hr::GameObject::GameObject(GameObject *parent)
    : _parent(parent)
{
    _name = "GameObject";
    _transform = new Transform(this);
    if (parent)
        parent->AddChild(this);
    Engine::Get()->AddEntity(this);
}

hr::GameObject::~GameObject()
{
}

void hr::GameObject::Start()
{
    for (auto [type, comp] : _components)
        if (comp->IsActive())
            comp->Start();
    // for (GameObject *child : _childs)
    //     if (child->IsActive())
    //         child->Start();
}

void hr::GameObject::Update()
{
    for (auto [type, comp] : _components)
        if (comp->IsActive())
            comp->Update();
    // for (GameObject *child : _childs)
    //     if (child->IsActive())
    //         child->Update();
}

void hr::GameObject::LateUpdate()
{
    for (auto [type, comp] : _components)
        if (comp->IsActive())
            comp->LateUpdate();
    // for (GameObject *child : _childs)
    //     if (child->IsActive())
    //         child->LateUpdate();
}

void hr::GameObject::End()
{
    for (auto [type, comp] : _components)
        if (comp->IsActive())
            comp->End();
    // for (GameObject *child : _childs)
    //     if (child->IsActive())
    //         child->End();
}

hr::GameObject *hr::GameObject::GetParent() const
{
    return _parent;
}

hr::Transform *hr::GameObject::GetTransform() const
{
    return _transform;
}

std::unordered_map<std::type_index, hr::Component *> hr::GameObject::GetComponents() const
{
    return _components;
}

void hr::GameObject::AddChild(GameObject *child)
{
    _childs.push_back(child);
}