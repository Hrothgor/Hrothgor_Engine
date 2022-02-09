/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** SaveSystem
*/

#include "SaveSystem.hpp"
#include "../Ecs/Engine.hpp"
#include "../Ecs/GameObject.hpp"

#include "../Components/Transform.hpp"

namespace hr {
    nlohmann::json SaveSystem::SaveEntity(GameObject *entity)
    {
        nlohmann::json json;

        json["uuid"] = entity->GetUUID().str();
        json["name"] = entity->GetName();
        json["transform"] = entity->GetTransform()->ToJson();
        for (auto [type, comp] : entity->GetComponents())
            json["components"].push_back({comp->GetName(), comp->ToJson()});
        for (auto &child : entity->GetChilds())
            json["childs"].push_back(SaveEntity(child));
        return json;
    }

    void SaveSystem::SaveProject(const std::string &name)
    {
        if (Engine::Get()->GetProjectName() == "")
            return;
        std::ofstream file("./Projects/" + name + "/save.json", std::ios::trunc);

        std::vector<GameObject *> _entities = Engine::Get()->GetRootEntities();
    
        nlohmann::json json;
        for (auto &entity : _entities)
            json["entities"].push_back(SaveEntity(entity));

        file << std::setw(4) << json;

        file.close();
    }
}

