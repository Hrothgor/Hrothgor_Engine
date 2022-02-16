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
        _velocity = Vector3Add(_velocity, velocity);
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