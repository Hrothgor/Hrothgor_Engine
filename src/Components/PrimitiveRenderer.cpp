/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** PrimitiveRenderer
*/

#include "PrimitiveRenderer.hpp"
#include "../RenderEngine/UI/UIElement.hpp"
#include "../RenderEngine/Master3DRenderer.hpp"
#include "PrimitiveCollider.hpp"
#include "../Ecs/GameObject.hpp"

namespace hr {
    PrimitiveRenderer::PrimitiveRenderer(GameObject *gameObject)
        : Component(gameObject)
    {
        _name = "PrimitiveRenderer";

        PrimitiveCollider *primitiveCollider = GetGameObject()->TryGetComponent<PrimitiveCollider>();
        if (primitiveCollider) {
            _type = primitiveCollider->GetType();
            _cubeWidth = primitiveCollider->GetCubeWidth() - 0.1;
            _cubeHeight = primitiveCollider->GetCubeHeight() - 0.1;
            _cubeLength = primitiveCollider->GetCubeLength() - 0.1;
            _sphereRadius = primitiveCollider->GetSphereRadius() - 0.1;
        } else {
            _type = CUBE;
        }
        SetModel(_type);
    }

    PrimitiveRenderer::~PrimitiveRenderer()
    {
        if (_model.meshCount > 0)
            UnloadModel(_model);
    }

    void PrimitiveRenderer::Update()
    {
        Master3DRenderer::Get()->RegisterObject(GetGameObject());
    }

    Model PrimitiveRenderer::GetModel() const 
    {
        return _model;
    }

    PrimitiveMeshType PrimitiveRenderer::GetType() const
    {
        return _type;
    }

    void PrimitiveRenderer::SetModel(PrimitiveMeshType type)
    {
        _type = type;
        if (_model.meshCount > 0)
            UnloadModel(_model);
        switch (type) {
            case CUBE:
                _model = LoadModelFromMesh(GenMeshCube(_cubeWidth, _cubeHeight, _cubeLength));
                break;
            case SPHERE:
                _model = LoadModelFromMesh(GenMeshSphere(_sphereRadius, _sphereRings, _sphereSlices));
                break;
            case PLANE:
                _model = LoadModelFromMesh(GenMeshPlane(_planeWidth, _planeLength, _planeResolution, _planeResolution));
                break;
        }
    }

    float PrimitiveRenderer::GetCubeWidth() const
    {
        return _cubeWidth;
    }

    void PrimitiveRenderer::SetCubeWidth(float width)
    {
        _cubeWidth = width;
        if (_type == CUBE)
            SetModel(_type);
    }

    float PrimitiveRenderer::GetCubeHeight() const
    {
        return _cubeHeight;
    }

    void PrimitiveRenderer::SetCubeHeight(float height)
    {
        _cubeHeight = height;
        if (_type == CUBE)
            SetModel(_type);
    }

    float PrimitiveRenderer::GetCubeLength() const
    {
        return _cubeLength;
    }

    void PrimitiveRenderer::SetCubeLength(float length)
    {
        _cubeLength = length;
        if (_type == CUBE)
            SetModel(_type);
    }

    float PrimitiveRenderer::GetSphereRadius() const
    {
        return _sphereRadius;
    }

    void PrimitiveRenderer::SetSphereRadius(float radius)
    {
        _sphereRadius = radius;
        if (_type == SPHERE)
            SetModel(_type);
    }

    int PrimitiveRenderer::GetSphereRings() const
    {
        return _sphereRings;
    }

    void PrimitiveRenderer::SetSphereRings(int rings)
    {
        _sphereRings = rings;
        if (_type == SPHERE)
            SetModel(_type);
    }

    int PrimitiveRenderer::GetSphereSlices() const
    {
        return _sphereSlices;
    }

    void PrimitiveRenderer::SetSphereSlices(int slices)
    {
        _sphereSlices = slices;
        if (_type == SPHERE)
            SetModel(_type);
    }

    float PrimitiveRenderer::GetPlaneWidth() const
    {
        return _planeWidth;
    }

    void PrimitiveRenderer::SetPlaneWidth(float width)
    {
        _planeWidth = width;
        if (_type == PLANE)
            SetModel(_type);
    }

    float PrimitiveRenderer::GetPlaneLength() const
    {
        return _planeLength;
    }

    void PrimitiveRenderer::SetPlaneLength(float length)
    {
        _planeLength = length;
        if (_type == PLANE)
            SetModel(_type);
    }

    int PrimitiveRenderer::GetPlaneResolution() const
    {
        return _planeResolution;
    }

    void PrimitiveRenderer::SetPlaneResolution(int resolution)
    {
        _planeResolution = resolution;
        if (_type == PLANE)
            SetModel(_type);
    }

    void PrimitiveRenderer::ImGuiRender()
    {
        std::vector<std::string> enumNames = {"Cube", "Sphere", "Plane"};
        UIElement::EnumField("Primitive", [this](){return GetType();}, [this](int val){SetModel((PrimitiveMeshType)val);}, enumNames);
        switch (_type) {
            case CUBE:
                UIElement::FloatField("Cube Width", [this](){return GetCubeWidth();}, [this](float val){SetCubeWidth(val);});
                UIElement::FloatField("Cube Height", [this](){return GetCubeHeight();}, [this](float val){SetCubeHeight(val);});
                UIElement::FloatField("Cube Length", [this](){return GetCubeLength();}, [this](float val){SetCubeLength(val);});
                break;
            case SPHERE:
                UIElement::FloatField("Sphere Radius", [this](){return GetSphereRadius();}, [this](float val){SetSphereRadius(val);});
                UIElement::IntField("Sphere Rings", [this](){return GetSphereRings();}, [this](int val){SetSphereRings(val);}, 1, 4, 30);
                UIElement::IntField("Sphere Slices", [this](){return GetSphereSlices();}, [this](int val){SetSphereSlices(val);}, 1, 4, 100);
                break;
            case PLANE:
                UIElement::FloatField("Plane Width", [this](){return GetPlaneWidth();}, [this](float val){SetPlaneWidth(val);});
                UIElement::FloatField("Plane Length", [this](){return GetPlaneLength();}, [this](float val){SetPlaneLength(val);});
                UIElement::IntField("Plane Resolution", [this](){return GetPlaneResolution();}, [this](int val){SetPlaneResolution(val);}, 1, 1, 1000);
                break;
        }
    }

    nlohmann::json PrimitiveRenderer::ToJson() const
    {
        nlohmann::json json;

        json["type"] = (int)_type;
        json["cube"]["width"] = _cubeWidth;
        json["cube"]["height"] = _cubeHeight;
        json["cube"]["length"] = _cubeLength;
        json["sphere"]["radius"] = _sphereRadius;
        json["sphere"]["rings"] = _sphereRings;
        json["sphere"]["slices"] = _sphereSlices;
        json["plane"]["width"] = _planeWidth;
        json["plane"]["length"] = _planeLength;
        json["plane"]["resolution"] = _planeResolution;

        return json;
    }

    void PrimitiveRenderer::FromJson(const nlohmann::json &json)
    {
        _type = (PrimitiveMeshType)json["type"].get<int>();
        _cubeWidth = json["cube"]["width"].get<float>();
        _cubeHeight = json["cube"]["height"].get<float>();
        _cubeLength = json["cube"]["length"].get<float>();
        _sphereRadius = json["sphere"]["radius"].get<float>();
        _sphereRings = json["sphere"]["rings"].get<int>();
        _sphereSlices = json["sphere"]["slices"].get<int>();
        _planeWidth = json["plane"]["width"].get<float>();
        _planeLength = json["plane"]["length"].get<float>();
        _planeResolution = json["plane"]["resolution"].get<int>();
        SetModel(_type);
    }
}