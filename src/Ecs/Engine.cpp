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

Engine *Engine::instance = nullptr;

Engine::Engine()
{
}

Engine::~Engine()
{
}

void Engine::LoadScene()
{
    GameObject *mainCamera = new GameObject();
    mainCamera->SetName("mainCamera");
    mainCamera->AddComponent<Components::MainCamera3D>();

    GameObject *test1 = new GameObject();
    test1->SetName("test1");
    test1->AddComponent<Components::MeshRenderer>()->Load("ressources/dragon.obj");
}

void Engine::Start()
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

void Engine::Update()
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

void Engine::End()
{
    for (auto ent : _entities)
        ent->End();
    CloseAudioDevice();
    CloseWindow();
}

GameObject *Engine::Find(const std::string &name)
{
    for (auto ent : _entities)
        if (ent->GetName() == name)
            return ent;
    return nullptr;
}

GameObject *Engine::Instantiate(GameObject *object, GameObject *parent)
{
    return nullptr;
}

void Engine::Destroy(GameObject *object, float t)
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

void Engine::AddEntity(GameObject *gameObject)
{
    _entities.push_back(gameObject);
}