/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** SphereCollider
*/

#include "SphereCollider.hpp"
#include "Components/Transform.hpp"
#include "RenderEngine/UI/UIElement.hpp"
#include "PhysicsEngine/Implementations/PhysicsAlgo.hpp"

namespace hr {
    SphereCollider::SphereCollider(GameObject *gameObject)
        : Component(gameObject)
    {
        _name = "SphereCollider";
    }

    SphereCollider::~SphereCollider()
    {
    }

    CollisionPoints SphereCollider::TestCollision(const Transform *transform, const Collider *collider, const Transform *colliderTransform) const
    {
        return collider->TestCollision(colliderTransform, this, transform);
    }

    CollisionPoints SphereCollider::TestCollision(const Transform *transform, const SphereCollider *sphere, const Transform *sphereTransform) const
    {
        return PhysicsAlgo::FindSphereSphereCollisionPoints(this, transform, sphere, sphereTransform);
    }

    CollisionPoints SphereCollider::TestCollision(const Transform *transform, const BoxCollider *box, const Transform *boxTransform) const
    {
        CollisionPoints points = PhysicsAlgo::FindSphereBoxCollisionPoints(this, transform, box, boxTransform);
        points.Swap = true;
        return points; 
    }

    void SphereCollider::SetOffset(Vector3 offset)
    {
        _offset = offset;
    }

    Vector3 SphereCollider::GetOffset() const
    {
        return _offset;
    }

    float SphereCollider::GetRadius() const
    {
        return _radius;
    }

    void SphereCollider::SetRadius(float radius)
    {
        _radius = radius;
    }

    void SphereCollider::ImGuiRender()
    {
        UIElement::Vector3Field("Offset", [this](){return GetOffset();}, [this](Vector3 vec){SetOffset(vec);});
        UIElement::FloatField("Sphere Radius", [this](){return GetRadius();}, [this](float val){SetRadius(val);});
    }

    void SphereCollider::OnDrawGizmos()
    {
        Transform *transform = GetTransform();
        Vector3 pos = transform->GetPositionWorld() + _offset;

        DrawSphereWires(pos, _radius,
            10, 10, GREEN);
    }

    nlohmann::json SphereCollider::ToJson() const
    {
        nlohmann::json json;

        json["offset"] = {_offset.x, _offset.y, _offset.z};
        json["radius"] = _radius;

        return json;
    }

    void SphereCollider::FromJson(const nlohmann::json &json)
    {
        _offset = {json["offset"][0].get<float>(), json["offset"][1].get<float>(), json["offset"][2].get<float>()};
        _radius = json["radius"].get<float>();
    }

    Component *SphereCollider::Clone(GameObject *gameObject)
    {
        SphereCollider *ret = new SphereCollider(gameObject);
        ret->SetOffset(_offset);
        ret->SetRadius(_radius);
        return ret;
    }
}
