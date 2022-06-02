/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** CreatePrimitive
*/

#include "CreatePrimitive.hpp"
#include "GameObject.hpp"
#include "Components/Collider/SphereCollider.hpp"
#include "Components/Collider/BoxCollider.hpp"
#include "Components/RigidBody.hpp"
#include "Components/Transform.hpp"
#include "Components/MeshRenderer.hpp"
#include "Components/Light.hpp"

namespace hr {
    GameObject *CreatePrimitive::CreateEmpty(GameObject *parent)
    {
        GameObject *gameObject = new GameObject(parent);
        gameObject->SetName("GameObject");
        return gameObject;
    }

    GameObject *CreatePrimitive::CreateSphere(GameObject *parent)
    {
        GameObject *sphere = new GameObject(parent);
        sphere->SetName("Sphere");
        sphere->AddComponent<SphereCollider>();
        sphere->AddComponent<MeshRenderer>()->LoadMeshFromPath("Engine/Ressources/sphere.obj");
        sphere->AddComponent<RigidBody>();
        return sphere;
    }

    GameObject *CreatePrimitive::CreateBox(GameObject *parent)
    {
        GameObject *box = new GameObject(parent);
        box->SetName("Box");
        box->AddComponent<BoxCollider>();
        box->AddComponent<MeshRenderer>()->LoadMeshFromPath("Engine/Ressources/cube.obj");
        box->AddComponent<RigidBody>();
        return box;
    }

    GameObject *CreatePrimitive::CreateMesh(GameObject *parent)
    {
        GameObject *mesh = new GameObject(parent);
        mesh->SetName("Mesh");
        mesh->AddComponent<MeshRenderer>();
        mesh->AddComponent<RigidBody>();
        return mesh;
    }

    GameObject *CreatePrimitive::CreateLight(GameObject *parent)
    {
        GameObject *light = new GameObject(parent);
        light->SetName("Light");
        light->AddComponent<Light>();
        return light;
    }
}
