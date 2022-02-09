/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** MeshRenderer
*/

#include "MeshRenderer.hpp"
#include "../RenderEngine/UI/UIElement.hpp"
#include "../RenderEngine/Master3DRenderer.hpp"
#include "../Ecs/GameObject.hpp"
#include "MeshFilter.hpp"

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
    }

    void MeshRenderer::Update()
    {
        MeshFilter *meshFilter = GetGameObject()->TryGetComponent<MeshFilter>();
        if (meshFilter) {
            if (meshFilter->GetModel().meshCount > 0 && _texture.id != 0)
                meshFilter->GetModel().materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = _texture;
            Master3DRenderer::Get()->RegisterObject(GetGameObject());
        }
    }

    void MeshRenderer::LoadTextureFromPath(const std::string &path)
    {
        if (std::filesystem::exists(path) && ends_with(path, ".png")) {
            if (_texture.id != 0)
                UnloadTexture(_texture);
            _texture = LoadTexture(path.c_str());
            _texturePath = path;
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

    void MeshRenderer::ImGuiRender()
    {
        UIElement::StringField("Texture", [this](){return GetTexturePath();}, [this](const std::string &str){LoadTextureFromPath(str);});
    }

    nlohmann::json MeshRenderer::ToJson() const
    {
        nlohmann::json json;

        json["texturePath"] = _texturePath;

        return json;
    }

    void MeshRenderer::FromJson(const nlohmann::json &json)
    {
        _texturePath = json["texturePath"].get<std::string>();

        LoadTextureFromPath(_texturePath);
    }
}
