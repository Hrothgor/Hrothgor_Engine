/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** LoadSystem
*/

#include "LoadSystem.hpp"
#include "../Ecs/Engine.hpp"
#include "../Ecs/GameObject.hpp"

#include "../Components/Light.hpp"
#include "../Components/MainCamera3D.hpp"
#include "../Components/MeshRenderer.hpp"
#include "../Components/Transform.hpp"

namespace hr {
    GameObject *LoadSystem::LoadEntity(const nlohmann::json &json)
    {
        GameObject *gameObject = new GameObject();

        gameObject->SetUUID(json["uuid"].get<std::string>());
        gameObject->SetName(json["name"].get<std::string>());
        gameObject->GetTransform()->FromJson(json["transform"]);
        if (json.contains("components"))
            for (auto &comp : json["components"]) {
                std::string name = comp[0].get<std::string>();
                if (name == "MeshRenderer") gameObject->AddComponent<MeshRenderer>()->FromJson(comp[1]);
                else if (name == "Light") gameObject->AddComponent<Light>()->FromJson(comp[1]);
            }
        if (json.contains("childs"))
            for (auto &jsonChild : json["childs"])
                gameObject->AddChild(LoadEntity(jsonChild));

        return gameObject;
    }

    void LoadSystem::LoadProject(const std::string &fileName)
    {
        std::ifstream file(fileName);
        if (!file.is_open())
            throw std::runtime_error("File not found");

        nlohmann::json json;
        file >> json;
        file.close();

        Engine::Get()->ClearEntities();
        for (auto &jsonEntity : json["entities"])
            Engine::Get()->AddEntity(LoadEntity(jsonEntity));
        
        Engine::Get()->Start();
    }

    void LoadSystem::NewProject()
    {
    }
}