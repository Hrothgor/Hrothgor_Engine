/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** LoadSystem
*/

#include "LoadSystem.hpp"
#include "Ecs/Engine.hpp"
#include "RenderEngine/AssetsManager.hpp"
#include "Ecs/GameObject.hpp"

#include "Components/Light.hpp"
#include "Components/MainCamera3D.hpp"
#include "Components/Collider/BoxCollider.hpp"
#include "Components/Collider/SphereCollider.hpp"
#include "Components/MeshRenderer.hpp"
#include "Components/Transform.hpp"
#include "Components/RigidBody.hpp"
#include "Components/Particles/ParticleSystem.hpp"

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
                else if (name == "BoxCollider") gameObject->AddComponent<BoxCollider>()->FromJson(comp[1]);
                else if (name == "SphereCollider") gameObject->AddComponent<SphereCollider>()->FromJson(comp[1]);
                else if (name == "RigidBody") gameObject->AddComponent<RigidBody>()->FromJson(comp[1]);
                else if (name == "ParticleSystem") gameObject->AddComponent<ParticleSystem>()->FromJson(comp[1]);
            }
        if (json.contains("childs"))
            for (auto &jsonChild : json["childs"])
                gameObject->AddChild(LoadEntity(jsonChild));

        return gameObject;
    }

    void LoadSystem::LoadProject(const std::string &name)
    {
        // if (!std::filesystem::exists("Engine/Scenes/" + name + ".scn"))
        //     return;
        Engine::Get()->SetProjectName(name);
        Engine::Get()->SetSimulating(false);
        if (!std::filesystem::exists("Engine/Scenes/" + name + ".scn")) {
            Engine::Get()->ClearEntities();
            Engine::Get()->Start();
            return;
        }
        std::ifstream file("Engine/Scenes/" + name + ".scn");

        nlohmann::json json;
        file >> json;
        file.close();

        Engine::Get()->ClearEntities();
        for (auto &jsonEntity : json["entities"])
            Engine::Get()->AddEntity(LoadEntity(jsonEntity));
        
        Engine::Get()->Start();
    }
}