/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** PrimitiveCollider
*/

#include "PrimitiveCollider.hpp"
#include "../RenderEngine/UI/UIElement.hpp"
#include "Transform.hpp"
#include "../Ecs/GameObject.hpp"

namespace hr {
    PrimitiveCollider::PrimitiveCollider(GameObject *gameObject)
        : Component(gameObject)
    {
        _name = "PrimitiveCollider";

        MeshFilter *meshFilter = GetGameObject()->TryGetComponent<MeshFilter>();
        if (meshFilter) {
            _type = meshFilter->GetType();
            _cubeWidth = meshFilter->GetCubeWidth() + 0.1;
            _cubeHeight = meshFilter->GetCubeHeight() + 0.1;
            _cubeLength = meshFilter->GetCubeLength() + 0.1;
            _sphereRadius = meshFilter->GetSphereRadius() + 0.1;
            if (_type == PLANE) {
                _type = CUBE;
                _cubeWidth = meshFilter->GetPlaneWidth() + 0.1;
                _cubeHeight = 0.5;
                _cubeLength = meshFilter->GetPlaneLength() + 0.1;
            }
            if (_type == MESH)
                _type = CUBE;
        } else {
            _type = CUBE;
        }
        SetMesh(_type);
    }

    PrimitiveCollider::~PrimitiveCollider()
    {
        if (_mesh.triangleCount > 0)
            UnloadMesh(_mesh);
    }

    Mesh PrimitiveCollider::GetMesh() const
    {
        return _mesh;
    }

    PrimitiveMeshType PrimitiveCollider::GetType() const
    {
        return _type;
    }

    void PrimitiveCollider::SetMesh(PrimitiveMeshType type)
    {
        _type = type;
        if (_mesh.triangleCount > 0)
            UnloadMesh(_mesh);
        switch (type) {
            case CUBE:
                _mesh = GenMeshCube(_cubeWidth, _cubeHeight, _cubeLength);
                break;
            case SPHERE:
                _mesh = GenMeshSphere(_sphereRadius, 10, 10);
                break;
            case PLANE:
                break;
            case MESH:
                break;
        }
    }

    float PrimitiveCollider::GetCubeWidth() const
    {
        return _cubeWidth;
    }

    void PrimitiveCollider::SetCubeWidth(float width)
    {
        _cubeWidth = width;
        if (_type == CUBE)
            SetMesh(_type);
    }

    float PrimitiveCollider::GetCubeHeight() const
    {
        return _cubeHeight;
    }

    void PrimitiveCollider::SetCubeHeight(float height)
    {
        _cubeHeight = height;
        if (_type == CUBE)
            SetMesh(_type);
    }

    float PrimitiveCollider::GetCubeLength() const
    {
        return _cubeLength;
    }

    void PrimitiveCollider::SetCubeLength(float length)
    {
        _cubeLength = length;
        if (_type == CUBE)
            SetMesh(_type);
    }

    float PrimitiveCollider::GetSphereRadius() const
    {
        return _sphereRadius;
    }

    void PrimitiveCollider::SetSphereRadius(float radius)
    {
        _sphereRadius = radius;
        if (_type == SPHERE)
            SetMesh(_type);
    }

    void PrimitiveCollider::ImGuiRender()
    {
        std::vector<std::string> enumNames = {"Cube", "Sphere"};
        UIElement::EnumField("Primitive", [this](){return GetType();}, [this](int val){SetMesh((PrimitiveMeshType)val);}, enumNames);
        switch (_type) {
            case CUBE:
                UIElement::FloatField("Cube Width", [this](){return GetCubeWidth();}, [this](float val){SetCubeWidth(val);});
                UIElement::FloatField("Cube Height", [this](){return GetCubeHeight();}, [this](float val){SetCubeHeight(val);});
                UIElement::FloatField("Cube Length", [this](){return GetCubeLength();}, [this](float val){SetCubeLength(val);});
                break;
            case SPHERE:
                UIElement::FloatField("Sphere Radius", [this](){return GetSphereRadius();}, [this](float val){SetSphereRadius(val);});
                break;
            case PLANE:
                break;
            case MESH:
                break;
        }
    }

    void PrimitiveCollider::OnDrawGizmos()
    {
        Transform *transform = GetTransform();
        AxisAngle axisAngle = transform->GetRotationAxisAngle();

        switch (_type) {
            case CUBE:
                rlPushMatrix();
                rlTranslatef(transform->GetPositionWorld().x, transform->GetPositionWorld().y, transform->GetPositionWorld().z);
                rlRotatef(axisAngle.angle, axisAngle.axis.x, axisAngle.axis.y, axisAngle.axis.z);
                rlTranslatef(-transform->GetPositionWorld().x, -transform->GetPositionWorld().y, -transform->GetPositionWorld().z);
                DrawCubeWires(transform->GetPositionWorld(), _cubeWidth, _cubeHeight, _cubeLength, GREEN);
                rlPopMatrix();
                break;
            case SPHERE:
                DrawSphereWires(transform->GetPositionWorld(), _sphereRadius,
                            10, 10, GREEN);
                break;
            case PLANE:
                break;
            case MESH:
                break;
        }
    }

    nlohmann::json PrimitiveCollider::ToJson() const
    {
        nlohmann::json json;

        json["type"] = (int)_type;
        json["cube"]["width"] = _cubeWidth;
        json["cube"]["height"] = _cubeHeight;
        json["cube"]["length"] = _cubeLength;
        json["sphere"]["radius"] = _sphereRadius;

        return json;
    }

    void PrimitiveCollider::FromJson(const nlohmann::json &json)
    {
        _type = (PrimitiveMeshType)json["type"].get<int>();
        _cubeWidth = json["cube"]["width"].get<float>();
        _cubeHeight = json["cube"]["height"].get<float>();
        _cubeLength = json["cube"]["length"].get<float>();
        _sphereRadius = json["sphere"]["radius"].get<float>();
        SetMesh(_type);
    }
}