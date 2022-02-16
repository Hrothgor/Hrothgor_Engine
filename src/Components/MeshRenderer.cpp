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
#include "../Tools/String.hpp"
#include "../RenderEngine/AssetsManager.hpp"

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
        if (AssetsManager::Get()->EngineTextureContains(path)) {
            if (_texture.id != 0)
                UnloadTexture(_texture);
            _texturePath = path;
            _texture = AssetsManager::Get()->EngineTextureGet(path);
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

    Component *MeshRenderer::Clone(GameObject *gameObject)
    {
        MeshRenderer *ret = new MeshRenderer(gameObject);
        ret->LoadTextureFromPath(_texturePath);
        return ret;
    }
}
