/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** BoxCollider
*/

#include "BoxCollider.hpp"
#include "Components/Transform.hpp"
#include "RenderEngine/UI/UIElement.hpp"
#include "PhysicsEngine/Implementations/PhysicsAlgo.hpp"

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

    Vector3 BoxCollider::GetSize() const
    {
        return {_width * GetTransform()->GetScaleWorld().x, _height * GetTransform()->GetScaleWorld().y, _length * GetTransform()->GetScaleWorld().z};
    }

    float BoxCollider::GetWidth() const
    {
        return _width;
    }

    void BoxCollider::SetWidth(float width)
    {
        _width = width;
    }

    float BoxCollider::GetHeight() const
    {
        return _height;
    }

    void BoxCollider::SetHeight(float height)
    {
        _height = height;
    }

    float BoxCollider::GetLength() const
    {
        return _length;
    }

    void BoxCollider::SetLength(float length)
    {
        _length = length;
    }

    void BoxCollider::ImGuiRender()
    {
        UIElement::Vector3Field("Offset", [this](){return GetOffset();}, [this](Vector3 vec){SetOffset(vec);});
        UIElement::FloatField("Cube Width", [this](){return GetWidth();}, [this](float val){SetWidth(val);});
        UIElement::FloatField("Cube Height", [this](){return GetHeight();}, [this](float val){SetHeight(val);});
        UIElement::FloatField("Cube Length", [this](){return GetLength();}, [this](float val){SetLength(val);});
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
        DrawCubeWires(pos, GetSize().x * 2, GetSize().y * 2, _length * GetSize().z * 2, GREEN);
        rlPopMatrix();
    }

    nlohmann::json BoxCollider::ToJson() const
    {
        nlohmann::json json;

        json["offset"] = {_offset.x, _offset.y, _offset.z};
        json["width"] = _width;
        json["height"] = _height;
        json["length"] = _length;

        return json;
    }

    void BoxCollider::FromJson(const nlohmann::json &json)
    {
        _offset = {json["offset"][0].get<float>(), json["offset"][1].get<float>(), json["offset"][2].get<float>()};
        _width = json["width"].get<float>();
        _height = json["height"].get<float>();
        _length = json["length"].get<float>();
    }

    Component *BoxCollider::Clone(GameObject *gameObject)
    {
        BoxCollider *ret = new BoxCollider(gameObject);
        ret->SetOffset(_offset);
        ret->SetWidth(_width);
        ret->SetHeight(_height);
        ret->SetLength(_length);
        return ret;
    }
}