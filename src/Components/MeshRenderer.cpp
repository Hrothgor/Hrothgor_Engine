/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** MeshRenderer
*/

#include "MeshRenderer.hpp"
#include "../RenderEngine/Master3DRenderer.hpp"

hr::MeshRenderer::MeshRenderer(GameObject *gameObject)
    : Component(gameObject)
{
}

hr::MeshRenderer::~MeshRenderer()
{
}

void hr::MeshRenderer::Update()
{
    Master3DRenderer::Get()->RegisterObject(GetGameObject());
}

void hr::MeshRenderer::Load(const std::string &path, const std::string &texturePath)
{
    if (std::filesystem::exists(path)) {
        _model = LoadModel(path.c_str());
        if (texturePath != "" && std::filesystem::exists(texturePath)) {
            _texture = LoadTexture(texturePath.c_str());
            _model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = _texture;
        }
    }
}

Model hr::MeshRenderer::GetModel() const
{
    return _model;
}

Texture2D hr::MeshRenderer::GetTexture() const
{
    return _texture;
}