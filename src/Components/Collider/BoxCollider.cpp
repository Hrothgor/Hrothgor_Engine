/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** BoxCollider
*/

#include "BoxCollider.hpp"
#include "../Transform.hpp"
#include "../../RenderEngine/UI/UIElement.hpp"
#include "../../PhysicsEngine/PhysicsAlgo.hpp"

namespace hr {
    BoxCollider::BoxCollider(GameObject *gameObject)
        : Component(gameObject)
    {
        _name = "BoxCollider";
    }

    BoxCollider::~BoxCollider()
    {
    }

    CollisionPoints BoxCollider::TestCollision(const Transform *transform, const Collider *collider, const Transform *colliderTransform) const
    {
        return collider->TestCollision(colliderTransform, this, transform);
    }

    CollisionPoints BoxCollider::TestCollision(const Transform *transform, const SphereCollider *sphere, const Transform *sphereTransform) const
    {
        return PhysicsAlgo::FindSphereBoxCollisionPoints(sphere, sphereTransform, this, transform);
    }

    CollisionPoints BoxCollider::TestCollision(const Transform *transform, const BoxCollider *box, const Transform *boxTransform) const
    {
        return PhysicsAlgo::FindBoxBoxCollisionPoints(this, transform, box, boxTransform);
    }

    void BoxCollider::SetOffset(Vector3 offset)
    {
        _offset = offset;
    }

    Vector3 BoxCollider::GetOffset() const
    {
        return _offset;
    }

    float BoxCollider::GetCubeWidth() const
    {
        return _cubeWidth;
    }

    void BoxCollider::SetCubeWidth(float width)
    {
        _cubeWidth = width;
    }

    float BoxCollider::GetCubeHeight() const
    {
        return _cubeHeight;
    }

    void BoxCollider::SetCubeHeight(float height)
    {
        _cubeHeight = height;
    }

    float BoxCollider::GetCubeLength() const
    {
        return _cubeLength;
    }

    void BoxCollider::SetCubeLength(float length)
    {
        _cubeLength = length;
    }

    void BoxCollider::ImGuiRender()
    {
        UIElement::Vector3Field("Offset", [this](){return GetOffset();}, [this](Vector3 vec){SetOffset(vec);});
        UIElement::FloatField("Cube Width", [this](){return GetCubeWidth();}, [this](float val){SetCubeWidth(val);});
        UIElement::FloatField("Cube Height", [this](){return GetCubeHeight();}, [this](float val){SetCubeHeight(val);});
        UIElement::FloatField("Cube Length", [this](){return GetCubeLength();}, [this](float val){SetCubeLength(val);});
    }

    void BoxCollider::OnDrawGizmos()
    {
        Transform *transform = GetTransform();
        Vector3 pos = Vector3Add(transform->GetPositionWorld(), _offset);
        AxisAngle axisAngle = transform->GetRotationAxisAngle();

        rlPushMatrix();
        rlTranslatef(pos.x, pos.y, pos.z);
        rlRotatef(axisAngle.angle, axisAngle.axis.x, axisAngle.axis.y, axisAngle.axis.z);
        rlTranslatef(-pos.x, -pos.y, -pos.z);
        DrawCubeWires(pos, _cubeWidth, _cubeHeight, _cubeLength, GREEN);
        rlPopMatrix();
    }

    nlohmann::json BoxCollider::ToJson() const
    {
        nlohmann::json json;

        json["offset"] = {_offset.x, _offset.y, _offset.z};
        json["width"] = _cubeWidth;
        json["height"] = _cubeHeight;
        json["length"] = _cubeLength;

        return json;
    }

    void BoxCollider::FromJson(const nlohmann::json &json)
    {
        _offset = {json["offset"][0].get<float>(), json["offset"][1].get<float>(), json["offset"][2].get<float>()};
        _cubeWidth = json["width"].get<float>();
        _cubeHeight = json["height"].get<float>();
        _cubeLength = json["length"].get<float>();
    }

    Component *BoxCollider::Clone(GameObject *gameObject)
    {
        BoxCollider *ret = new BoxCollider(gameObject);
        ret->SetOffset(_offset);
        ret->SetCubeWidth(_cubeWidth);
        ret->SetCubeHeight(_cubeHeight);
        ret->SetCubeLength(_cubeLength);
        return ret;
    }
}