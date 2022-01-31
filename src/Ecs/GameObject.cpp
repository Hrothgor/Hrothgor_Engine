/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** GameObject
*/

#include "GameObject.hpp"
#include "../Components/Transform.hpp"
#include "Engine.hpp"

GameObject::GameObject(GameObject *parent)
    : _parent(parent)
{
    _name = "GameObject";
    _transform = new Components::Transform(this);
    if (parent)
        parent->AddChild(this);
    Engine::Get()->AddEntity(this);
}

GameObject::~GameObject()
{
}

void GameObject::Start()
{
    for (auto [type, comp] : _components)
        if (comp->IsActive())
            comp->Start();
    // for (GameObject *child : _childs)
    //     if (child->IsActive())
    //         child->Start();
}

void GameObject::Update()
{
    for (auto [type, comp] : _components)
        if (comp->IsActive())
            comp->Update();
    // for (GameObject *child : _childs)
    //     if (child->IsActive())
    //         child->Update();
}

void GameObject::LateUpdate()
{
    for (auto [type, comp] : _components)
        if (comp->IsActive())
            comp->LateUpdate();
    // for (GameObject *child : _childs)
    //     if (child->IsActive())
    //         child->LateUpdate();
}

void GameObject::End()
{
    for (auto [type, comp] : _components)
        if (comp->IsActive())
            comp->End();
    // for (GameObject *child : _childs)
    //     if (child->IsActive())
    //         child->End();
}

GameObject *GameObject::GetParent() const
{
    return _parent;
}

Components::Transform *GameObject::GetTransform() const
{
    return _transform;
}

std::unordered_map<std::type_index, Component *> GameObject::GetComponents() const
{
    return _components;
}

void GameObject::AddChild(GameObject *child)
{
    _childs.push_back(child);
}