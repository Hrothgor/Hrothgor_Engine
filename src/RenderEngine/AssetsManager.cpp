/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** AssetsManager
*/

#include "AssetsManager.hpp"
#include "../Tools/String.hpp"

namespace hr {
    AssetsManager *AssetsManager::instance = nullptr;

    AssetsManager::AssetsManager()
    {
    }

    AssetsManager::~AssetsManager()
    {
    }

    void AssetsManager::Start()
    {
        for (const auto &entry : std::filesystem::directory_iterator("ressources")) {
            if (String::EndWith(entry.path(), ".obj"))
                _engineModels[entry.path()] = LoadModel(entry.path().c_str());
            if (String::EndWith(entry.path(), ".png"))
                _engineTextures[entry.path()] = LoadTexture(entry.path().c_str());
        }
    }

    void AssetsManager::LoadProject(const std::string &path)
    {
        for (auto [key, model] : _projectModels)
            UnloadModel(model);
        for (auto [key, texture] : _projectTextures)
            UnloadTexture(texture);
        _projectModels.clear();
        _projectTextures.clear();
        for (const auto &entry : std::filesystem::directory_iterator(path)) {
            if (String::EndWith(entry.path(), ".obj"))
                _projectModels[entry.path()] = LoadModel(entry.path().c_str());
            if (String::EndWith(entry.path(), ".png"))
                _projectTextures[entry.path()] = LoadTexture(entry.path().c_str());
        }
    }

    // std::map<std::string, Texture> AssetsManager::GetEngineTexture() const
    // {
    //     return _engineTextures;
    // }

    // std::map<std::string, Model> AssetsManager::GetEngineModel() const
    // {
    //     return _engineModels;
    // }

    bool AssetsManager::EngineTextureContains(const std::string &key) const
    {
        return _engineTextures.contains(key);
    }

    bool AssetsManager::EngineModelContains(const std::string &key) const
    {
        return _engineModels.contains(key);
    }

    Texture2D AssetsManager::EngineTextureGet(const std::string &key)
    {
        return _engineTextures[key];
    }

    Model AssetsManager::EngineModelGet(const std::string &key)
    {
        return _engineModels[key];
    }

    // std::map<std::string, Texture> AssetsManager::GetProjectTexture() const
    // {
    //     return _projectTextures;
    // }

    // std::map<std::string, Model> AssetsManager::GetProjectModel() const
    // {
    //     return _projectModels;
    // }

    bool AssetsManager::ProjectTextureContains(const std::string &key) const
    {
        return _projectTextures.contains(key);
    }

    bool AssetsManager::ProjectModelContains(const std::string &key) const
    {
        return _projectModels.contains(key);
    }

    Texture2D AssetsManager::ProjectTextureGet(const std::string &key)
    {
        return _projectTextures[key];
    }

    Model AssetsManager::ProjectModelGet(const std::string &key)
    {
        return _projectModels[key];
    }
}
