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
}

void hr::Engine::Start()
{
    SetTraceLogLevel(TraceLogLevel::LOG_WARNING);
    InitWindow(WIDTH, HEIGHT, "Physics Engine");
    SetConfigFlags(FLAG_MSAA_4X_HINT);
	ToggleFullscreen();
    InitAudioDevice();

    LoadScene();
    for (auto ent : _entities)
        ent->Start();
}

void hr::Engine::Update()
{
    while (!WindowShouldClose())
    {
        BeginDrawing();
        {
            for (auto ent : _entities)
                ent->Update();
            for (auto ent : _entities)
                ent->LateUpdate();
            DisplayManager::Get()->Clear(DARKBLUE);
            DisplayManager::Get()->Draw();
        }
        EndDrawing();
    }
}

void hr::Engine::End()
{
    for (auto ent : _entities)
        ent->End();
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

hr::GameObject *hr::Engine::Instantiate(GameObject *object, GameObject *parent)
{
    return nullptr;
}

void hr::Engine::Destroy(GameObject *object, float t)
{
    if (t > 0) {
        for (auto it = _entities.begin(); it != _entities.end(); it++)
            if (*it == object) {
                _entities.erase(it);
                delete *it;
                return;
            }
    } else {
        t -= GetFrameTime();
    }
}

void hr::Engine::AddEntity(GameObject *gameObject)
{
    _entities.push_back(gameObject);
}