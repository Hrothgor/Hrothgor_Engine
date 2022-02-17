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
#include "../PhysicsEngine/PhysicsWorld.hpp"

namespace hr {
    RigidBody::RigidBody(GameObject *gameObject)
        : Component(gameObject)
    {
        _name = "RigidBody";
        _velocity = Vector3Zero();
        _angularVelocity = Vector3Zero();
        _force = Vector3Zero();
    }

    RigidBody::~RigidBody()
    {
    }

    void RigidBody::UpdateOnSimulation()
    {
        PhysicsWorld::Get()->RegisterObject(GetGameObject());
    }

    float RigidBody::GetMass() const
    {
        return _mass;
    }
    
    float RigidBody::GetInvMass() const
    {
        return 1 / _mass;
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

    Vector3 RigidBody::GetForce() const
    {
        return _force;
    }

    void RigidBody::SetForce(Vector3 force)
    {
        _force = force;
    }

    void RigidBody::AddForce(Vector3 force)
    {
        _force = Vector3Add(_force, force);
    }

    Vector3 RigidBody::GetVelocity() const
    {
        return _velocity;
    }

    void RigidBody::SetVelocity(Vector3 velocity)
    {
        _velocity = velocity;
    }

    void RigidBody::AddVelocity(Vector3 velocity)
    {
        _velocity = Vector3Add(_velocity, Vector3Scale(velocity, GetInvMass()));
    }

    Vector3 RigidBody::GetAngularVelocity() const
    {
        return _angularVelocity;
    }

    void RigidBody::SetAngularVelocity(Vector3 angularVelocity)
    {
        _angularVelocity = angularVelocity;
    }

    void RigidBody::AddAngularVelocity(Vector3 angularVelocity)
    {
        _angularVelocity = Vector3Add(_angularVelocity, Vector3Multiply(Vector3One(), angularVelocity)); // TODO InertiaTensor
    }

    bool RigidBody::GetIsDynamic() const
    {
        return _isDynamic;
    }

    void RigidBody::SetIsDynamic(bool isDynamic)
    {
        _isDynamic = isDynamic;
    }

    void RigidBody::ImGuiRender()
    {
        UIElement::FloatField("Mass", [this](){return GetMass();}, [this](float val){SetMass(val);});
        UIElement::CheckBox("Use Gravity", [this](){return GetUseGravity();}, [this](bool val){SetUseGravity(val);});
        UIElement::CheckBox("Is Dynamic", [this](){return GetIsDynamic();}, [this](bool val){SetIsDynamic(val);});
    }

    nlohmann::json RigidBody::ToJson() const
    {
        nlohmann::json json;

        json["mass"] = _mass;
        json["useGravity"] = _useGravity;
        json["isDynamic"] = _isDynamic;

        return json;
    }

    void RigidBody::FromJson(const nlohmann::json &json)
    {
        _mass = json["mass"].get<float>();
        _useGravity = json["useGravity"].get<bool>();
        _isDynamic = json["isDynamic"].get<bool>();
    }

    Component *RigidBody::Clone(GameObject *gameObject)
    {
        RigidBody *ret = new RigidBody(gameObject);
        ret->SetMass(_mass);
        ret->SetUseGravity(_useGravity);
        ret->SetIsDynamic(_isDynamic);
        return ret;
    }
}