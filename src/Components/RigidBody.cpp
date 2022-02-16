/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** RigidBody
*/

#include "RigidBody.hpp"
#include "../RenderEngine/UI/UIElement.hpp"
#include "ImGuizmo.h"
#include "Transform.hpp"
#include "../Ecs/GameObject.hpp"

namespace hr {
    RigidBody::RigidBody(GameObject *gameObject)
        : Component(gameObject)
    {
        _name = "RigidBody";
    }

    RigidBody::~RigidBody()
    {
    }

    void RigidBody::UpdateOnSimulation()
    {
        Transform *transform = GetTransform();
        transform->Translate({0, -9.8f * _mass * GetFrameTime(), 0});
        // if (_isKinematic)
        //     return;
        // _velocity = Vector3Add(_velocity, _acceleration);
        // _position = Vector3Add(_position, _velocity);
        // _acceleration = Vector3Zero();
    }

    float RigidBody::GetMass() const
    {
        return _mass;
    }

    void RigidBody::SetMass(float mass)
    {
        _mass = mass;
    }

    bool RigidBody::GetUseGravity() const
    {
        return _useGravity;
    }

    void RigidBody::SetUseGravity(bool useGravity)
    {
        _useGravity = useGravity;
    }

    void RigidBody::ImGuiRender()
    {
        UIElement::FloatField("Mass", [this](){return GetMass();}, [this](float val){SetMass(val);});
        UIElement::CheckBox("Use Gravity", [this](){return GetUseGravity();}, [this](bool val){SetUseGravity(val);});
    }

    nlohmann::json RigidBody::ToJson() const
    {
        nlohmann::json json;

        json["mass"] = _mass;
        json["useGravity"] = _useGravity;

        return json;
    }

    void RigidBody::FromJson(const nlohmann::json &json)
    {
        _mass = json["mass"].get<float>();
        _useGravity = json["useGravity"].get<bool>();
    }

    Component *RigidBody::Clone(GameObject *gameObject)
    {
        RigidBody *ret = new RigidBody(gameObject);
        ret->SetMass(_mass);
        ret->SetUseGravity(_useGravity);
        return ret;
    }
}