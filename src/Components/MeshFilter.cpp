/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** MeshFilter
*/

#include "MeshFilter.hpp"
#include "../RenderEngine/UI/UIElement.hpp"
#include "../RenderEngine/Master3DRenderer.hpp"
#include "../Ecs/GameObject.hpp"
#include "../Tools/String.hpp"
#include "../RenderEngine/AssetsManager.hpp"

namespace hr {
    MeshFilter::MeshFilter(GameObject *gameObject)
        : Component(gameObject)
    {
        _name = "MeshFilter";

        _type = CUBE;
        SetModel(_type);
    }

    MeshFilter::~MeshFilter()
    {
        if (_model.meshCount > 0)
            UnloadModel(_model);
    }

    void MeshFilter::Update()
    {
    }

    Model MeshFilter::GetModel() const 
    {
        return _model;
    }

    PrimitiveMeshType MeshFilter::GetType() const
    {
        return _type;
    }

    void MeshFilter::SetModel(PrimitiveMeshType type)
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
            case MESH:
                _model = AssetsManager::Get()->GetModel(_meshPath);
                break;
        }
    }

    float MeshFilter::GetCubeWidth() const
    {
        return _cubeWidth;
    }

    void MeshFilter::SetCubeWidth(float width)
    {
        _cubeWidth = width;
        if (_type == CUBE)
            SetModel(_type);
    }

    float MeshFilter::GetCubeHeight() const
    {
        return _cubeHeight;
    }

    void MeshFilter::SetCubeHeight(float height)
    {
        _cubeHeight = height;
        if (_type == CUBE)
            SetModel(_type);
    }

    float MeshFilter::GetCubeLength() const
    {
        return _cubeLength;
    }

    void MeshFilter::SetCubeLength(float length)
    {
        _cubeLength = length;
        if (_type == CUBE)
            SetModel(_type);
    }

    float MeshFilter::GetSphereRadius() const
    {
        return _sphereRadius;
    }

    void MeshFilter::SetSphereRadius(float radius)
    {
        _sphereRadius = radius;
        if (_type == SPHERE)
            SetModel(_type);
    }

    int MeshFilter::GetSphereRings() const
    {
        return _sphereRings;
    }

    void MeshFilter::SetSphereRings(int rings)
    {
        _sphereRings = rings;
        if (_type == SPHERE)
            SetModel(_type);
    }

    int MeshFilter::GetSphereSlices() const
    {
        return _sphereSlices;
    }

    void MeshFilter::SetSphereSlices(int slices)
    {
        _sphereSlices = slices;
        if (_type == SPHERE)
            SetModel(_type);
    }

    float MeshFilter::GetPlaneWidth() const
    {
        return _planeWidth;
    }

    void MeshFilter::SetPlaneWidth(float width)
    {
        _planeWidth = width;
        if (_type == PLANE)
            SetModel(_type);
    }

    float MeshFilter::GetPlaneLength() const
    {
        return _planeLength;
    }

    void MeshFilter::SetPlaneLength(float length)
    {
        _planeLength = length;
        if (_type == PLANE)
            SetModel(_type);
    }

    int MeshFilter::GetPlaneResolution() const
    {
        return _planeResolution;
    }

    void MeshFilter::SetPlaneResolution(int resolution)
    {
        _planeResolution = resolution;
        if (_type == PLANE)
            SetModel(_type);
    }

    std::string MeshFilter::GetMeshPath() const
    {
        return _meshPath;
    }

    void MeshFilter::LoadMeshFromPath(const std::string &path)
    {
        if (AssetsManager::Get()->ModelContains(path)) {
            _meshPath = path;
            if (_type == MESH)
                SetModel(_type);
        }
    }

    void MeshFilter::ImGuiRender()
    {
        std::vector<std::string> enumNames = {"Cube", "Sphere", "Plane", "Mesh"};
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
            case MESH:
                UIElement::StringField("Model", [this](){return GetMeshPath();}, [this](const std::string &str){LoadMeshFromPath(str);});
                break;
        }
    }

    nlohmann::json MeshFilter::ToJson() const
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
        json["mesh"]["path"] = _meshPath;

        return json;
    }

    void MeshFilter::FromJson(const nlohmann::json &json)
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
        _meshPath = json["mesh"]["path"].get<std::string>();
        SetModel(_type);
    }

    Component *MeshFilter::Clone(GameObject *gameObject)
    {
        MeshFilter *ret = new MeshFilter(gameObject);
        ret->SetCubeWidth(_cubeWidth);
        ret->SetCubeHeight(_cubeHeight);
        ret->SetCubeLength(_cubeLength);
        ret->SetSphereRadius(_sphereRadius);
        ret->SetSphereRings(_sphereRings);
        ret->SetSphereSlices(_sphereSlices);
        ret->SetPlaneWidth(_planeWidth);
        ret->SetPlaneLength(_planeLength);
        ret->SetPlaneResolution(_planeResolution);
        ret->LoadMeshFromPath(_meshPath);
        ret->SetModel(_type);
        return ret;
    }
}