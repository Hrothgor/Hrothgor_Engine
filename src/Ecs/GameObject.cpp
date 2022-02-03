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
    if (_parent)
        _parent->AddChild(this);
    Engine::Get()->AddEntity(this);
}

hr::GameObject::~GameObject()
{
}

void hr::GameObject::Start()
{
    if (!IsActive())
        return;
    for (auto [type, comp] : _components)
        if (comp->IsActive())
            comp->Start();
    for (GameObject *child : _childs)
        if (child->IsActive())
            child->Start();
}

void hr::GameObject::Update()
{
    if (!IsActive())
        return;
    for (auto [type, comp] : _components)
        if (comp->IsActive())
            comp->Update();
    for (GameObject *child : _childs)
        if (child->IsActive())
            child->Update();
}

void hr::GameObject::LateUpdate()
{
    if (!IsActive())
        return;
    for (auto [type, comp] : _components)
        if (comp->IsActive())
            comp->LateUpdate();
    for (GameObject *child : _childs)
        if (child->IsActive())
            child->LateUpdate();
}

void hr::GameObject::End()
{
    if (!IsActive())
        return;
    for (auto [type, comp] : _components)
        if (comp->IsActive())
            comp->End();
    for (GameObject *child : _childs)
        if (child->IsActive())
            child->End();
}

hr::GameObject *hr::GameObject::GetParent() const
{
    return _parent;
}

std::vector<hr::GameObject *> hr::GameObject::GetChilds() const
{
    return _childs;
}

hr::Transform *hr::GameObject::GetTransform() const
{
    return _transform;
}

std::vector<std::pair<std::type_index, hr::Component *>> hr::GameObject::GetComponents() const
{
    return _components;
}

void hr::GameObject::SetComponents(std::vector<std::pair<std::type_index, hr::Component *>> components)
{
    _components = components;
}

void hr::GameObject::AddChild(GameObject *child)
{
    _childs.push_back(child);
}

void hr::GameObject::RemoveChild(GameObject *child)
{
    // _childs.erase(
    //     std::remove_if(_childs.begin(), _childs.end(), [&](GameObject *object) {
    //         return object->GetUUID() == child->GetUUID();
    //     }),
    //     _childs.end());
    _childs.erase(std::remove(_childs.begin(), _childs.end(), child), _childs.end());
}

void hr::GameObject::DetachFromParent()
{
    if (!_parent)
        return;
    _parent->RemoveChild(this);
    _parent = nullptr;
}

void hr::GameObject::SetParent(GameObject *parent)
{
    if (GetUUID() == parent->GetUUID() || _parent == parent || ParentIsChild(parent))
        return;
    DetachFromParent();
    _parent = parent;
    if (_parent)
        _parent->AddChild(this);
}

bool hr::GameObject::ParentIsChild(GameObject *parent)
{
    for (GameObject *child : _childs) {
        if (child->GetUUID() == parent->GetUUID())
            return true;
        if (child->ParentIsChild(parent))
            return true;
    }
    return false;
}

void hr::GameObject::Destroy()
{
    End();
    DetachFromParent();

    for (GameObject *child : _childs)
        child->Destroy();

    Engine::Get()->RemoveEntity(this);
}