/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** Transform
*/

#include "Transform.hpp"
#include "../Ecs/GameObject.hpp"
#include "../RenderEngine/UI/UIElement.hpp"
#include "ImGuizmo.h"

namespace hr {
    Transform::Transform(GameObject *gameObject)
        : Component(gameObject)
    {
        _name = "Transform";
        _position = Vector3Zero();
        _rotation = Vector3Zero();
        _scale = Vector3One();
        _front = Vector3Zero();
    }

    Transform::~Transform()
    {
    }

    void Transform::Update()
    {
        _front.x = cos(DEG2RAD * _rotation.y) * cos(DEG2RAD * _rotation.z);
        _front.y = cos(DEG2RAD * _rotation.y) * sin(DEG2RAD * _rotation.z);
        _front.z = sin(DEG2RAD * _rotation.y);
        _front = Vector3Normalize(_front);
    }

    void Transform::Translate(Vector3 vec)
    {
        _position = Vector3Add(_position, vec);
    }

    void Transform::Rotate(Vector3 vec)
    {
        _rotation = Vector3Add(_rotation, vec);
    }

    void Transform::Rotate(float x, float y, float z)
    {
        _rotation = Vector3Add(_rotation, (Vector3){x, y, z});
    }

    // Matrix Transform::GetTransformMatrix() const
    // {
    //     AxisAngle rot = GetRotationAxisAngle();
    //     Matrix rotation = MatrixRotate(rot.axis, rot.angle);
    //     Matrix scale = MatrixScale(_scale.x, _scale.y, _scale.z);
    //     Matrix translate = MatrixTranslate(_position.x, _position.y, _position.z);

    //     return MatrixMultiply(MatrixMultiply(translate, rotation), scale);
    // }

    Vector3 Transform::GetPosition() const
    {
        return _position;
    }

    Vector3 Transform::GetPositionWorld() const
    {
        if (GetGameObject()->GetParent())
            return Vector3Add(GetGameObject()->GetParent()->GetTransform()->GetPositionWorld(), _position);
        return _position;
    }

    void Transform::SetPosition(Vector3 pos)
    {
        _position = pos;
    }

    void Transform::SetPosition(float x, float y, float z)
    {
        _position = {x, y, z};
    }

    void Transform::SetPositionFromWorld(float x, float y, float z)
    {
        Vector3 parentWorldPos = Vector3Zero();
        if (GetGameObject()->GetParent())
            parentWorldPos = GetGameObject()->GetParent()->GetTransform()->GetPositionWorld();
        _position = Vector3Subtract({x, y, z}, parentWorldPos);
    }

    Vector3 Transform::GetRotation() const
    {
        return _rotation;
    }

    Vector3 Transform::GetRotationRadian() const
    {
        return {_rotation.x * DEG2RAD, _rotation.y * DEG2RAD, _rotation.z * DEG2RAD};
    }

    Quaternion Transform::GetRotationQuaternion() const
    {
        return EulerToQuaternion(_rotation);
    }

    AxisAngle Transform::GetRotationAxisAngle() const
    {
        AxisAngle ret;
        QuaternionToAxisAngle(GetRotationQuaternion(), &ret.axis, &ret.angle);
        ret.angle *= RAD2DEG;
        return ret;
    }

    Matrix Transform::GetRotationMatrix() const
    {
        return MatrixRotateXYZ({DEG2RAD * _rotation.x, DEG2RAD *_rotation.y, DEG2RAD *_rotation.z});
    }

    void Transform::SetRotation(Vector3 rotation)
    {
        _rotation = rotation;
    }

    void Transform::SetRotation(float x, float y, float z)
    {
        _rotation = {x, y, z};
    }

    Vector3 Transform::GetScale() const
    {
        return _scale;
    }

    void Transform::SetScale(Vector3 scale)
    {
        _scale = scale;
    }

    void Transform::SetScale(float x, float y, float z)
    {
        _scale = {x, y, z};
    }

    Vector3 Transform::GetFront() const
    {
        return _front;
    }

    Quaternion Transform::EulerToQuaternion(Vector3 euler)
    {
        float yaw = euler.z * DEG2RAD;
        float pitch = euler.y * DEG2RAD;
        float roll = euler.x * DEG2RAD;

        double cy = cos(yaw * 0.5);
        double sy = sin(yaw * 0.5);
        double cp = cos(pitch * 0.5);
        double sp = sin(pitch * 0.5);
        double cr = cos(roll * 0.5);
        double sr = sin(roll * 0.5);

        Quaternion q;
        q.w = cr * cp * cy + sr * sp * sy;
        q.x = sr * cp * cy - cr * sp * sy;
        q.y = cr * sp * cy + sr * cp * sy;
        q.z = cr * cp * sy - sr * sp * cy;

        return q;
    }

    void Transform::ImGuiRender()
    {
        UIElement::Vector3Field("Position", [this](){return GetPosition();}, [this](Vector3 vec){SetPosition(vec);});
        UIElement::Vector3Field("Rotation", [this](){return GetRotation();}, [this](Vector3 vec){SetRotation(vec);});
        UIElement::Vector3Field("Scale", [this](){return GetScale();}, [this](Vector3 vec){SetScale(vec);});
    }

    nlohmann::json Transform::ToJson() const
    {
        nlohmann::json json;

        json["position"] = {_position.x, _position.y, _position.z};
        json["rotation"] = {_rotation.x, _rotation.y, _rotation.z};
        json["scale"] = {_scale.x, _scale.y, _scale.z};

        return json;
    }

    void Transform::FromJson(const nlohmann::json &json)
    {
        _position = {json["position"][0].get<float>(), json["position"][1].get<float>(), json["position"][2].get<float>()};
        _rotation = {json["rotation"][0].get<float>(), json["rotation"][1].get<float>(), json["rotation"][2].get<float>()};
        _scale = {json["scale"][0], json["scale"][1], json["scale"][2]};
    }
}