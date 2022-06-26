/*
** EPITECH PROJECT, 2022
** Hrothgor_Engine
** File description:
** SphereSender
*/

#include "SphereSender.hpp"
#include "Engine.hpp"

namespace hr {
    SphereSender::SphereSender(GameObject *gameObject)
        : Component(gameObject)
    {
        _name = "SphereSender";
    }

    SphereSender::~SphereSender()
    {
    }

    void SphereSender::UpdateOnSimulation()
    {
        if (IsKeyPressed(KEY_K)) {
            GameObject *sphere = new GameObject(GetGameObject());
            sphere->AddComponent<SphereCollider>()->SetRadius(6.1);
            sphere->AddComponent<MeshRenderer>()->LoadMeshFromPath("Engine/Ressources/sphere.obj");
            sphere->GetTransform()->SetScale((Vector3){6, 6, 6});
            sphere->AddComponent<RigidBody>()->SetVelocity({(float)(rand() % 20 - 10), 20.0, (float)(rand() % 20 - 10)});
            Engine::Get()->Instantiate(sphere);
        }
    }

    nlohmann::json SphereSender::ToJson() const
    {
        nlohmann::json json;

        return json;
    }

    void SphereSender::FromJson(const nlohmann::json &json)
    {
        (void)json;
    }

    Component *SphereSender::Clone(GameObject *gameObject)
    {
        SphereSender *ret = new SphereSender(gameObject);
        return ret;
    }
}