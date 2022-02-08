/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** PrimitiveRenderer
*/

#include "PrimitiveRenderer.hpp"
#include "../RenderEngine/UI/UIElement.hpp"
#include "../RenderEngine/Master3DRenderer.hpp"

namespace hr {
    PrimitiveRenderer::PrimitiveRenderer(GameObject *gameObject)
        : Component(gameObject)
    {
        _name = "PrimitiveRenderer";

        _type = CUBE;
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

    PrimitiveMesh PrimitiveRenderer::GetType() const
    {
        return _type;
    }

    void PrimitiveRenderer::SetModel(PrimitiveMesh type)
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
        std::vector<std::string> meshNames = {"Cube", "Sphere", "Plane"};
        UIElement::EnumField("Primitive", [this](){return GetType();}, [this](int val){SetModel((PrimitiveMesh)val);}, meshNames);
        switch (_type) {
            case CUBE:
                UIElement::FloatField("Cube Width", [this](){return GetCubeWidth();}, [this](float val){SetCubeWidth(val);});
                UIElement::FloatField("Cube Height", [this](){return GetCubeHeight();}, [this](float val){SetCubeHeight(val);});
                UIElement::FloatField("Cube Length", [this](){return GetCubeLength();}, [this](float val){SetCubeLength(val);});
                break;
            case SPHERE:
                UIElement::FloatField("Sphere Radius", [this](){return GetSphereRadius();}, [this](float val){SetSphereRadius(val);});
                UIElement::IntField("Sphere Rings", [this](){return GetSphereRings();}, [this](int val){SetSphereRings(val);});
                UIElement::IntField("Sphere Slices", [this](){return GetSphereSlices();}, [this](int val){SetSphereSlices(val);});
                break;
            case PLANE:
                UIElement::FloatField("Plane Width", [this](){return GetPlaneWidth();}, [this](float val){SetPlaneWidth(val);});
                UIElement::FloatField("Plane Length", [this](){return GetPlaneLength();}, [this](float val){SetPlaneLength(val);});
                UIElement::IntField("Plane Resolution", [this](){return GetPlaneResolution();}, [this](int val){SetPlaneResolution(val);});
                break;
        }
    }

    nlohmann::json PrimitiveRenderer::ToJson() const
    {
        nlohmann::json json;

        return json;
    }

    void PrimitiveRenderer::FromJson(const nlohmann::json &json)
    {
        (void)json;
    }
}