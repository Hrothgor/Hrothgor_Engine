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

#include "Collider/SphereCollider.hpp"
#include "Collider/BoxCollider.hpp"

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
        if (_mass == 0)
            return 0;
        return 1 / _mass;
    }

    Matrix RigidBody::GetInvTensor() const
    {
        if (_mass == 0)
            return {0, 0, 0, 0,
                    0, 0, 0, 0,
                    0, 0, 0, 0,
                    0, 0, 0, 0};
        
        float ix = 0;
        float iy = 0;
        float iz = 0;
        float iw = 0;

        SphereCollider *sphereCollider = GetGameObject()->TryGetComponent<SphereCollider>();
        BoxCollider *boxCollider = GetGameObject()->TryGetComponent<BoxCollider>();
        if (_mass != 0 && sphereCollider) {
            float r2 = sphereCollider->GetRadius() * sphereCollider->GetRadius();
            float fraction = (2.0 / 5.0);

            ix = r2 * _mass * fraction;
            iy = r2 * _mass * fraction;
            iz = r2 * _mass * fraction;
            iw = 1.0;
        } else if (_mass != 0 && boxCollider) {
            Vector3 size = Vector3Scale(boxCollider->GetSize(), 2);
            float fraction = (1.0 / 12.0);

            float x2 = size.x * size.x;
            float y2 = size.y * size.y;
            float z2 = size.z * size.z;

            ix = (y2 + z2) * _mass * fraction;
            iy = (x2 + z2) * _mass * fraction;
            iz = (x2 + y2) * _mass * fraction;
            iw = 1.0;
        }

        return MatrixInvert(
            {ix, 0, 0, 0,
            0, iy, 0, 0,
            0, 0, iz, 0,
            0, 0, 0, iw});
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
        Vector3 angVel;
        Matrix invTensor = GetInvTensor();
        angVel.x = angularVelocity.x * invTensor.m0 + angularVelocity.y * invTensor.m1 + angularVelocity.z * invTensor.m2 + 0.0 * invTensor.m3;
        angVel.y = angularVelocity.x * invTensor.m4 + angularVelocity.y * invTensor.m5 + angularVelocity.z * invTensor.m6 + 0.0 * invTensor.m7;
        angVel.z = angularVelocity.x * invTensor.m8 + angularVelocity.y * invTensor.m6 + angularVelocity.z * invTensor.m10 + 0.0 * invTensor.m11;
        
        _angularVelocity = Vector3Add(_angularVelocity, angVel);
    }

    bool RigidBody::GetIsDynamic() const
    {
        return _isDynamic;
    }

    void RigidBody::SetIsDynamic(bool isDynamic)
    {
        _isDynamic = isDynamic;
    }
    
    float RigidBody::GetStaticFriction() const
    {
        return _staticFriction;
    }

    void RigidBody::SetStaticFriction(float staticFriction)
    {
        _staticFriction = staticFriction;
    }

    float RigidBody::GetDynamicFriction() const
    {
        return _dynamicFriction;
    }

    void RigidBody::SetDynamicFriction(float dynamicFriction)
    {
        _dynamicFriction = dynamicFriction;
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