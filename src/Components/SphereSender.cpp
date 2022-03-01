/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** SphereSender
*/

#include "SphereSender.hpp"
#include "../Ecs/GameObject.hpp"
#include "Collider/SphereCollider.hpp"
#include "MeshFilter.hpp"
#include "MeshRenderer.hpp"
#include "RigidBody.hpp"
#include "../Ecs/Engine.hpp"

namespace hr {
    SphereSender::SphereSender(GameObject *gameObject)
        : Component(gameObject)
    {
        _name = "SphereSender";
    }

    SphereSender::~SphereSender()
    {
    }

    void SphereSender::Update()
    {
        if (IsKeyPressed(KEY_K)) {
            GameObject *sphere = new GameObject(GetGameObject());
            sphere->AddComponent<SphereCollider>()->SetRadius(6.1);
            sphere->AddComponent<MeshFilter>();
            MeshFilter *mf = sphere->GetComponent<MeshFilter>();
            mf->SetModel(SPHERE);
            mf->SetSphereRings(20);
            mf->SetSphereSlices(50);
            mf->SetSphereRadius(6);
            sphere->AddComponent<MeshRenderer>();
            sphere->AddComponent<RigidBody>()->SetVelocity({rand() % 20 - 10, 20, rand() % 20 - 10});
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