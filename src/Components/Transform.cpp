/*
** EPITECH PROJECT, 2022
** Hrothgor_Engine
** File description:
** Transform
*/

#include "Transform.hpp"
#include "Ecs/GameObject.hpp"
#include "RenderEngine/UI/UIElement.hpp"

#include "Guizmo.hpp"

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
        _front = GetLocalAxis()[0];
        _front = Vector3Normalize(_front);
    }

    void Transform::Translate(Vector3 vec)
    {
        _position = _position + vec;
    }

    void Transform::Rotate(Vector3 vec)
    {
        _rotation = _rotation + vec;
    }

    void Transform::Rotate(float x, float y, float z)
    {
        _rotation = _rotation + (Vector3){x, y, z};
    }

    Matrix Transform::GetTransformMatrix() const
    {
        float f[16];
        ImGuizmo::RecomposeMatrixFromComponents(Vector3ToFloat(GetPositionWorld()),
                                                Vector3ToFloat(GetRotation()),
                                                Vector3ToFloat(GetScaleWorld()),
                                                f);
        
        Matrix mat;
        mat.m0 = f[0];
        mat.m1 = f[1];
        mat.m2 = f[2];
        mat.m3 = f[3];
        mat.m4 = f[4];
        mat.m5 = f[5];
        mat.m6 = f[6];
        mat.m7 = f[7];
        mat.m8 = f[8];
        mat.m9 = f[9];
        mat.m10 = f[10];
        mat.m11 = f[11];
        mat.m12 = f[12];
        mat.m13 = f[13];
        mat.m14 = f[14];
        mat.m15 = f[15];

        return mat;
    }

    Vector3 Transform::GetPosition() const
    {
        return _position;
    }

    Vector3 Transform::GetPositionWorld() const
    {
        if (GetGameObject() && GetGameObject()->GetParent())
            return GetGameObject()->GetParent()->GetTransform()->GetPositionWorld() + _position;
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
        if (GetGameObject() && GetGameObject()->GetParent())
            parentWorldPos = GetGameObject()->GetParent()->GetTransform()->GetPositionWorld();
        _position = (Vector3){x, y, z} - parentWorldPos;
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

    Vector3 Transform::GetScaleWorld() const
    {
        if (GetGameObject() && GetGameObject()->GetParent())
            return Vector3Multiply(GetGameObject()->GetParent()->GetTransform()->GetScaleWorld(), _scale);
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

    void Transform::SetScaleFromWorld(float x, float y, float z)
    {
        Vector3 parentWorldScale = Vector3One();
        if (GetGameObject() && GetGameObject()->GetParent())
            parentWorldScale = GetGameObject()->GetParent()->GetTransform()->GetScaleWorld();
        _scale = {x / parentWorldScale.x, y / parentWorldScale.y, z / parentWorldScale.z};
    }

    Vector3 Transform::GetFront() const
    {
        return _front;
    }

    std::vector<Vector3> Transform::GetLocalAxis() const
    {
        std::vector<Vector3> ret;
        Quaternion q = EulerToQuaternion(_rotation);

        ret.push_back(Vector3RotateByQuaternion(Vector3{1, 0, 0}, q));
        ret.push_back(Vector3RotateByQuaternion(Vector3{0, 1, 0}, q));
        ret.push_back(Vector3RotateByQuaternion(Vector3{0, 0, 1}, q));
        return ret;
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

    Component *Transform::Clone(GameObject *gameObject)
    {
        Transform *ret = new Transform(gameObject);
        return ret;
    }
}