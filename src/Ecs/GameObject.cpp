/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** GameObject
*/

#include "GameObject.hpp"
#include "../Components/Transform.hpp"
#include "Engine.hpp"
#include "../RenderEngine/Master3DRenderer.hpp"

namespace hr {
    GameObject::GameObject(GameObject *parent)
        : _parent(parent)
    {
        _name = "GameObject";
        _transform = new Transform(this);
        if (_parent)
            _parent->AddChild(this);
    }

    GameObject::~GameObject()
    {
    }

    void GameObject::Start()
    {
        if (!IsActive())
            return;
        _transform->Start();
        for (auto [type, comp] : _components)
            if (comp->IsActive())
                comp->Start();
        for (GameObject *child : _childs)
            if (child->IsActive())
                child->Start();
    }

    void GameObject::Update()
    {
        if (!IsActive())
            return;
        if (Engine::Get()->GetSelectedEntity() == this)
            Master3DRenderer::Get()->RegisterGizmos(this);
        _transform->Update();
        for (auto [type, comp] : _components)
            if (comp->IsActive())
                comp->Update();
        for (GameObject *child : _childs)
            if (child->IsActive())
                child->Update();
    }

    void GameObject::LateUpdate()
    {
        if (!IsActive())
            return;
        _transform->LateUpdate();
        for (auto [type, comp] : _components)
            if (comp->IsActive())
                comp->LateUpdate();
        for (GameObject *child : _childs)
            if (child->IsActive())
                child->LateUpdate();
    }

    void GameObject::UpdateOnSimulation()
    {
        if (!IsActive())
            return;
        _transform->UpdateOnSimulation();
        for (auto [type, comp] : _components)
            if (comp->IsActive())
                comp->UpdateOnSimulation();
        for (GameObject *child : _childs)
            if (child->IsActive())
                child->UpdateOnSimulation();
    }

    void GameObject::OnDrawGizmos()
    {
        if (!IsActive())
            return;
        _transform->OnDrawGizmos();
        for (auto [type, comp] : _components)
            if (comp->IsActive())
                comp->OnDrawGizmos();
        // for (GameObject *child : _childs)
        //     if (child->IsActive())
        //         child->OnDrawGizmos();
    }


    void GameObject::End()
    {
        if (!IsActive())
            return;
        _transform->End();
        for (auto [type, comp] : _components)
            if (comp->IsActive())
                comp->End();
        for (GameObject *child : _childs)
            if (child->IsActive())
                child->End();
    }

    GameObject *GameObject::GetParent() const
    {
        return _parent;
    }

    std::vector<GameObject *> GameObject::GetChilds() const
    {
        return _childs;
    }

    Transform *GameObject::GetTransform() const
    {
        return _transform;
    }

    std::vector<std::pair<std::type_index, Component *>> GameObject::GetComponents() const
    {
        return _components;
    }

    void GameObject::SetComponents(std::vector<std::pair<std::type_index, Component *>> components)
    {
        _components = components;
    }

    void GameObject::AddChild(GameObject *child)
    {
        child->SetParent(this);
        _childs.push_back(child);
    }

    void GameObject::RemoveChild(GameObject *child)
    {
        // _childs.erase(
        //     std::remove_if(_childs.begin(), _childs.end(), [&](GameObject *object) {
        //         return object->GetUUID() == child->GetUUID();
        //     }),
        //     _childs.end());
        _childs.erase(std::remove(_childs.begin(), _childs.end(), child), _childs.end());
    }

    void GameObject::DetachFromParent()
    {
        if (!_parent)
            return;
        _parent->RemoveChild(this);
        _parent = nullptr;
    }

    void GameObject::SetParent(GameObject *parent)
    {
        if (GetUUID() == parent->GetUUID() || _parent == parent || ParentIsChild(parent))
            return;
        DetachFromParent();
        _parent = parent;
    }

    void GameObject::SetChilds(std::vector<GameObject *> childs)
    {
        _childs = childs;
    }

    bool GameObject::ParentIsChild(GameObject *parent)
    {
        for (GameObject *child : _childs) {
            if (child->GetUUID() == parent->GetUUID())
                return true;
            if (child->ParentIsChild(parent))
                return true;
        }
        return false;
    }

    void GameObject::Destroy()
    {
        End();
        DetachFromParent();

        for (GameObject *child : _childs)
            child->Destroy();

        Engine::Get()->RemoveEntity(this);
    }

    GameObject *GameObject::Clone()
    {
        GameObject *clone = new GameObject(_parent);
        clone->SetName(GetName());
        clone->SetActive(IsActive());
        clone->SetUUID(GetUUID().str());

        clone->GetTransform()->SetPosition(GetTransform()->GetPosition());
        clone->GetTransform()->SetRotation(GetTransform()->GetRotation());
        clone->GetTransform()->SetScale(GetTransform()->GetScale());
        std::vector<std::pair<std::type_index, Component *>> components;
        for (auto [type, comp] : _components)
            components.push_back({type, comp->Clone(clone)});
        clone->SetComponents(components);
        return clone;
    }
}