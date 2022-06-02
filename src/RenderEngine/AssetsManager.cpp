/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** AssetsManager
*/

#include "AssetsManager.hpp"
#include "Tools/String.hpp"

namespace hr {
    AssetsManager *AssetsManager::instance = nullptr;

    AssetsManager::AssetsManager()
    {
    }

    AssetsManager::~AssetsManager()
    {
        for (auto [path, model] : _models)
            UnloadModel(model);
        for (auto [path, texture] : _textures)
            UnloadTexture(texture);
    }

    void AssetsManager::Start()
    {
        for (const auto &entry : std::filesystem::directory_iterator("Engine/Ressources")) {
            if (String::EndWith(entry.path(), ".obj"))
                _models[entry.path()] = LoadModel(entry.path().c_str());
            if (String::EndWith(entry.path(), ".png"))
                _textures[entry.path()] = LoadTexture(entry.path().c_str());
        }

        for (const auto &entry : std::filesystem::directory_iterator("Engine/Ressources/Icons")) {
            if (String::EndWith(entry.path(), ".obj"))
                _models[entry.path()] = LoadModel(entry.path().c_str());
            if (String::EndWith(entry.path(), ".png"))
                _textures[entry.path()] = LoadTexture(entry.path().c_str());
        }
    }

    // std::map<std::string, Texture> AssetsManager::GetTextures() const
    // {
    //     return _textures;
    // }

    // std::map<std::string, Model> AssetsManager::GetModels() const
    // {
    //     return _models;
    // }

    bool AssetsManager::TextureContains(const std::string &key) const
    {
        return _textures.contains(key);
    }

    bool AssetsManager::ModelContains(const std::string &key) const
    {
        return _models.contains(key);
    }

    Texture2D AssetsManager::GetTexture(const std::string &key)
    {
        return _textures[key];
    }

    Texture2D *AssetsManager::GetTextureAddr(const std::string &key)
    {
        return &(_textures[key]);
    }

    Model AssetsManager::GetModel(const std::string &key)
    {
        return _models[key];
    }
}
