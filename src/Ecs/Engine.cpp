/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** Engine
*/

#include "Engine.hpp"
#include "../RenderEngine/DisplayManager.hpp"

#include "../Components/MeshRenderer.hpp"
#include "../Components/MainCamera3D.hpp"
#include "../Components/Transform.hpp"
#include "../Components/Light.hpp"

hr::Engine *hr::Engine::instance = nullptr;

hr::Engine::Engine()
{
}

hr::Engine::~Engine()
{
}

void hr::Engine::LoadScene()
{
    GameObject *mainCamera = new GameObject();
    mainCamera->SetName("mainCamera");
    mainCamera->AddComponent<MainCamera3D>();

    GameObject *lightDir = new GameObject();
    lightDir->SetName("lightDir");
    lightDir->AddComponent<Light>();

    GameObject *dragon = new GameObject();
    dragon->SetName("dragon");
    dragon->AddComponent<MeshRenderer>()->Load("ressources/dragon.obj");

    for (int i = 0; i < 5; i++) {
        GameObject *bomb = new GameObject(dragon);
        bomb->SetName("bomb" + std::to_string(i));
        bomb->AddComponent<MeshRenderer>()->Load("ressources/bomb.obj");
        bomb->GetTransform()->SetPosition(i * 10, 0, 0);
    }
}

void hr::Engine::Start()
{
    SetTraceLogLevel(TraceLogLevel::LOG_WARNING);
    InitWindow(WIDTH, HEIGHT, "Physics Engine");
    rlImGuiSetup(true);
    SetConfigFlags(FLAG_MSAA_4X_HINT);
	ToggleFullscreen();
    InitAudioDevice();

    LoadScene();
    for (auto ent : _entities)
        if (ent->GetParent() == nullptr)
            ent->Start();
}

void hr::Engine::Update()
{
    while (!WindowShouldClose())
    {
        BeginDrawing();
        {
            for (auto ent : _entities)
                if (ent->GetParent() == nullptr)
                    ent->Update();
            for (auto ent : _entities)
                if (ent->GetParent() == nullptr)
                    ent->LateUpdate();
            DisplayManager::Get()->Clear(DARKGRAY);
            DisplayManager::Get()->Draw();
        }
        EndDrawing();
    }
}

void hr::Engine::End()
{
    for (auto ent : _entities)
        if (ent->GetParent() == nullptr)
            ent->End();
    rlImGuiShutdown();
    CloseAudioDevice();
    CloseWindow();
}

hr::GameObject *hr::Engine::Find(const std::string &name)
{
    for (auto ent : _entities)
        if (ent->GetName() == name)
            return ent;
    return nullptr;
}

hr::GameObject *hr::Engine::Find(const UUIDv4::UUID &uuid)
{
    for (auto ent : _entities)
        if (ent->GetUUID() == uuid)
            return ent;
    return nullptr;
}

hr::GameObject *hr::Engine::Instantiate(GameObject *object, GameObject *parent)
{
    (void)object;
    (void)parent;
    // for unused parameter
    return nullptr;
}

void hr::Engine::Destroy(GameObject *object, float t)
{
    (void)t;
    // for unused parameter

    object->Destroy();

    // if (t > 0) {
    //     object->Destroy();
    // } else {
    //     t -= GetFrameTime();
    // }
    // NEED THREAD !
}

std::vector<hr::GameObject *> hr::Engine::GetEntities() const
{
    return _entities;
}

std::vector<hr::GameObject *> hr::Engine::GetRootEntities() const
{
    std::vector<GameObject *> rootEntities;
    for (auto ent : _entities) {
        if (ent->GetParent() == nullptr)
            rootEntities.push_back(ent);
    }
    return rootEntities;
}

void hr::Engine::AddEntity(GameObject *gameObject)
{
    _entities.push_back(gameObject);
}

void hr::Engine::RemoveEntity(GameObject *gameObject)
{
    _entities.erase(std::remove(_entities.begin(), _entities.end(), gameObject), _entities.end());
}

void hr::Engine::CreateEmptyGameObject()
{
    GameObject *gameObject = new GameObject();

    int i = 0;
    bool found = false;
    while (!found) {
        bool available = true;
        for (GameObject *ent : _entities) {
            if (ent->GetName() == "GameObject (" + std::to_string(i) + ")") {
                available = false;
                break;
            }
        }
        if (available) {
            gameObject->SetName("GameObject (" + std::to_string(i) + ")");
            found = true;
        }
        i++;
    }
}

hr::GameObject *hr::Engine::GetSelectedEntity() const
{
    return _selectedEntity;
}

void hr::Engine::SetSelectedEntity(GameObject *object)
{
    _selectedEntity = object;
}