/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** MeshRenderer
*/

#include "MeshRenderer.hpp"
#include "../RenderEngine/UI/UIElement.hpp"
#include "../RenderEngine/Master3DRenderer.hpp"

static inline bool ends_with(std::string const &value, std::string const &ending)
{
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

namespace hr {
    MeshRenderer::MeshRenderer(GameObject *gameObject)
        : Component(gameObject)
    {
        _name = "MeshRenderer";
    }

    MeshRenderer::~MeshRenderer()
    {
        if (_texture.id != 0)
            UnloadTexture(_texture);
        if (_model.meshCount > 0)
            UnloadModel(_model);
    }

    void MeshRenderer::Update()
    {
        Master3DRenderer::Get()->RegisterObject(GetGameObject());
    }

    void MeshRenderer::Load(const std::string &path, const std::string &texturePath)
    {
        if (std::filesystem::exists(path) && ends_with(path, ".obj")) {
            if (_model.meshCount > 0)
                UnloadModel(_model);
            _model = LoadModel(path.c_str());
            _modelPath = path;
            if (texturePath != "" && std::filesystem::exists(texturePath) && ends_with(texturePath, ".png")) {
                if (_texture.id != 0)
                    UnloadTexture(_texture);
                _texture = LoadTexture(texturePath.c_str());
                _texturePath = texturePath;
                _model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = _texture;
            }
        }
    }

    void MeshRenderer::LoadModelFromPath(const std::string &path)
    {
        if (std::filesystem::exists(path) && ends_with(path, ".obj")) {
            if (_model.meshCount > 0)
                UnloadModel(_model);
            _model = LoadModel(path.c_str());
            _modelPath = path;
            if (_texture.id != 0)
                _model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = _texture;
        }
    }

    void MeshRenderer::LoadTextureFromPath(const std::string &path)
    {
        if (std::filesystem::exists(path) && ends_with(path, ".png")) {
            if (_texture.id != 0)
                UnloadTexture(_texture);
            _texture = LoadTexture(path.c_str());
            _texturePath = path;
            if (_model.meshCount > 0)
                _model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = _texture;
        }
    }

    Model MeshRenderer::GetModel() const
    {
        return _model;
    }

    Texture2D MeshRenderer::GetTexture() const
    {
        return _texture;
    }

    std::string MeshRenderer::GetModelPath() const
    {
        return _modelPath;
    }

    std::string MeshRenderer::GetTexturePath() const
    {
        return _texturePath;
    }

    void MeshRenderer::ImGuiRender()
    {
        UIElement::StringField("Model", [this](){return GetModelPath();}, [this](const std::string &str){LoadModelFromPath(str);});
        UIElement::StringField("Texture", [this](){return GetTexturePath();}, [this](const std::string &str){LoadModelFromPath(str);});
    }

    nlohmann::json MeshRenderer::ToJson() const
    {
        nlohmann::json json;

        json["modelPath"] = _modelPath;
        json["texturePath"] = _texturePath;

        return json;
    }

    void MeshRenderer::FromJson(const nlohmann::json &json)
    {
        _modelPath = json["modelPath"].get<std::string>();
        _texturePath = json["texturePath"].get<std::string>();

        LoadModelFromPath(_modelPath);
        LoadTextureFromPath(_texturePath);
    }
}
