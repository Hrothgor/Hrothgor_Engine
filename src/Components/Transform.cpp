/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** Transform
*/

#include "Transform.hpp"
#include "../RenderEngine/UI/UIElement.hpp"

hr::Transform::Transform(GameObject *gameObject)
    : Component(gameObject)
{
    _name = "Transform";
    _position = Vector3Zero();
    _rotation = Vector3Zero();
    _scale = Vector3One();
}

hr::Transform::~Transform()
{
}

void hr::Transform::Translate(Vector3 vec)
{
    _position = Vector3Add(_position, vec);
}

void hr::Transform::Rotate(Vector3 vec)
{
    _rotation = Vector3Add(_rotation, vec);
}

Vector3 hr::Transform::GetPosition() const
{
    return _position;
}

void hr::Transform::SetPosition(Vector3 pos)
{
    _position = pos;
}

void hr::Transform::SetPosition(float x, float y, float z)
{
    _position = {x, y, z};
}

Vector3 hr::Transform::GetRotation() const
{
    return _rotation;
}

Quaternion hr::Transform::GetRotationQuaternion() const
{
    return EulerToQuaternion(_rotation);
}

hr::AxisAngle hr::Transform::GetRotationAxisAngle() const
{
    AxisAngle ret;
    QuaternionToAxisAngle(GetRotationQuaternion(), &ret.axis, &ret.angle);
    ret.angle *= RAD2DEG;
    return ret;
}

Matrix hr::Transform::GetRotationMatrix() const
{
    return MatrixRotateXYZ({DEG2RAD * _rotation.x, DEG2RAD *_rotation.y, DEG2RAD *_rotation.z});
}

void hr::Transform::SetRotation(Vector3 rotation)
{
    _rotation = rotation;
}

void hr::Transform::SetRotation(float x, float y, float z)
{
    _rotation = {x, y, z};
}

Vector3 hr::Transform::GetScale() const
{
    return _scale;
}

void hr::Transform::SetScale(Vector3 scale)
{
    _scale = scale;
}

void hr::Transform::SetScale(float x, float y, float z)
{
    _scale = {x, y, z};
}

Quaternion hr::Transform::EulerToQuaternion(Vector3 euler)
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

void hr::Transform::ImGuiRender()
{
    UIElement::Vector3Field("Position", [this](){return GetPosition();}, [this](Vector3 vec){SetPosition(vec);});
    UIElement::Vector3Field("Rotation", [this](){return GetRotation();}, [this](Vector3 vec){SetRotation(vec);});
    UIElement::Vector3Field("Scale", [this](){return GetScale();}, [this](Vector3 vec){SetScale(vec);});
}