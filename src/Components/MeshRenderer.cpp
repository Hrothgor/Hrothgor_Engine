/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** MeshRenderer
*/

#include "MeshRenderer.hpp"
#include "../RenderEngine/Master3DRenderer.hpp"

Components::MeshRenderer::MeshRenderer(GameObject *gameObject)
    : Component(gameObject)
{
}

Components::MeshRenderer::~MeshRenderer()
{
}

void Components::MeshRenderer::Update()
{
    Master3DRenderer::Get()->RegisterObject(GetGameObject());
}

void Components::MeshRenderer::Load(const std::string &path, const std::string &texturePath)
{
    if (std::filesystem::exists(path)) {
        _model = LoadModel(path.c_str());
        if (texturePath != "" && std::filesystem::exists(texturePath)) {
            _texture = LoadTexture(texturePath.c_str());
            _model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = _texture;
        }
    }
}

Model Components::MeshRenderer::GetModel() const
{
    return _model;
}

Texture2D Components::MeshRenderer::GetTexture() const
{
    return _texture;
}