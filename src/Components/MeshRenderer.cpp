/*
** EPITECH PROJECT, 2022
** Hrothgor_Engine
** File description:
** MeshRenderer
*/

#include "MeshRenderer.hpp"
#include "RenderEngine/UI/UIElement.hpp"
#include "Tools/SaveLoad/JsonManager.hpp"
#include "RenderEngine/Master3DRenderer.hpp"
#include "Ecs/GameObject.hpp"
#include "Tools/String.hpp"
#include "RenderEngine/AssetsManager.hpp"

namespace hr {
    MeshRenderer::MeshRenderer(GameObject *gameObject)
        : Component(gameObject)
    {
        _name = "MeshRenderer";
    }

    MeshRenderer::~MeshRenderer()
    {
    }

    void MeshRenderer::Update()
    {
        Master3DRenderer::Get()->RegisterObject(GetGameObject());
    }

    void MeshRenderer::LoadTextureFromPath(const std::string &path)
    {
        if (AssetsManager::Get()->TextureContains(path)) {
            _texturePath = path;
            _texture = AssetsManager::Get()->GetTexture(path);
        }
    }

    Texture2D MeshRenderer::GetTexture() const
    {
        return _texture;
    }

    std::string MeshRenderer::GetTexturePath() const
    {
        return _texturePath;
    }

    Model MeshRenderer::GetModel() const 
    {
        return _model;
    }

    std::string MeshRenderer::GetMeshPath() const
    {
        return _meshPath;
    }

    void MeshRenderer::LoadMeshFromPath(const std::string &path)
    {
        if (AssetsManager::Get()->ModelContains(path)) {
            _meshPath = path;
            _model = AssetsManager::Get()->GetModel(_meshPath);
        }
    }

    void MeshRenderer::SetColor(const Color &color)
    {
        _color = color;
    }

    Color MeshRenderer::GetColor() const
    {
        return _color;
    }

    void MeshRenderer::SetHasTransparency(const bool &bHasTransparency)
    {
        _bHasTransparency = bHasTransparency;
    }

    bool MeshRenderer::GetHasTransparency() const
    {
        return _bHasTransparency;
    }

    void MeshRenderer::ImGuiRender()
    {
        UIElement::ModelField("Mesh", [this](){return GetMeshPath();}, [this](const std::string &str){LoadMeshFromPath(str);});
        UIElement::TextureField("Texture", [this](){return GetTexturePath();}, [this](const std::string &str){LoadTextureFromPath(str);});
        UIElement::ColorField("Color", [this](){return GetColor();}, [this](const Color &val){SetColor(val);});
        UIElement::CheckBox("Has Transparency", [this](){return GetHasTransparency();}, [this](const bool &val){SetHasTransparency(val);});
    }

    nlohmann::json MeshRenderer::ToJson() const
    {
        nlohmann::json json;

        JsonManager::SaveString(json, "meshPath", _meshPath);
        JsonManager::SaveString(json, "texturePath", _texturePath);
        JsonManager::SaveColor(json, "color", _color);
        JsonManager::SaveBool(json, "hasTransparency", _bHasTransparency);

        return json;
    }

    void MeshRenderer::FromJson(const nlohmann::json &json)
    {
        _meshPath = JsonManager::LoadString(json, "meshPath");
        _texturePath = JsonManager::LoadString(json, "texturePath");
        _color = JsonManager::LoadColor(json, "color");
        _bHasTransparency = JsonManager::LoadBool(json, "hasTransparency");

        LoadTextureFromPath(_texturePath);
        LoadMeshFromPath(_meshPath);
    }

    Component *MeshRenderer::Clone(GameObject *gameObject)
    {
        MeshRenderer *ret = new MeshRenderer(gameObject);
        ret->LoadMeshFromPath(_meshPath);
        ret->LoadTextureFromPath(_texturePath);
        ret->SetColor(_color);
        ret->SetHasTransparency(_bHasTransparency);
        return ret;
    }
}
