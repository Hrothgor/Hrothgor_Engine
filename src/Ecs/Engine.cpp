/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** Engine
*/

#include "Engine.hpp"
#include "../RenderEngine/DisplayManager.hpp"
#include "../SaveLoad/SaveSystem.hpp"
#include "../SaveLoad/LoadSystem.hpp"

#include "../Components/MeshRenderer.hpp"
#include "../Components/MainCamera3D.hpp"
#include "../Components/Transform.hpp"
#include "../Components/Light.hpp"

namespace hr {
    Engine *Engine::instance = nullptr;

    Engine::Engine()
    {
        SetTraceLogLevel(TraceLogLevel::LOG_WARNING);
        InitWindow(WIDTH, HEIGHT, "Physics Engine");
        rlImGuiSetup(true);
        SetConfigFlags(FLAG_MSAA_4X_HINT);
        ToggleFullscreen();
        InitAudioDevice();
        
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking

        _mainCamera = new GameObject();
        _mainCamera->SetName("mainCamera");
        _mainCamera->AddComponent<MainCamera3D>();
        _mainCamera->GetTransform()->SetPosition(20, 20, 50);

    }

    Engine::~Engine()
    {
    }

    void Engine::Start()
    {
        DisplayManager::Get()->Start();
        _mainCamera->Start();
        for (auto ent : _entities)
            if (ent->GetParent() == nullptr)
                ent->Start();
    }

    void Engine::Update()
    {
        while (!WindowShouldClose())
        {
            BeginDrawing();
            {
                _mainCamera->Update();
                for (auto ent : _entities)
                    if (ent->GetParent() == nullptr)
                        ent->Update();
                _mainCamera->LateUpdate();
                for (auto ent : _entities)
                    if (ent->GetParent() == nullptr)
                        ent->LateUpdate();
                DisplayManager::Get()->Clear(DARKGRAY);
                DisplayManager::Get()->Draw();
            }
            EndDrawing();
            if (IsKeyPressed(KEY_SPACE))
                LoadSystem::LoadProject("./Projects/test1/save.json");
            if (IsKeyPressed(KEY_ENTER))
                SaveSystem::SaveProject();
        }
    }

    void Engine::End()
    {
        _mainCamera->End();
        for (auto ent : _entities)
            if (ent->GetParent() == nullptr)
                ent->End();
        DisplayManager::Get()->End();
        rlImGuiShutdown();
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

    GameObject *Engine::Find(const UUIDv4::UUID &uuid)
    {
        for (auto ent : _entities)
            if (ent->GetUUID() == uuid)
                return ent;
        return nullptr;
    }

    GameObject *Engine::Instantiate(GameObject *object, GameObject *parent)
    {
        (void)object;
        (void)parent;
        // for unused parameter
        return nullptr;
    }

    void Engine::Destroy(GameObject *object, float t)
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

    std::vector<GameObject *> Engine::GetEntities() const
    {
        return _entities;
    }

    std::vector<GameObject *> Engine::GetRootEntities() const
    {
        std::vector<GameObject *> rootEntities;
        for (auto ent : _entities) {
            if (ent->GetParent() == nullptr)
                rootEntities.push_back(ent);
        }
        return rootEntities;
    }

    void Engine::ClearEntities()
    {
        for (auto ent : _entities)
            if (ent->GetParent() == nullptr)
                ent->End();
        _entities.clear();
    }

    void Engine::AddEntity(GameObject *gameObject)
    {
        _entities.push_back(gameObject);
    }

    void Engine::RemoveEntity(GameObject *gameObject)
    {
        // TODO maybe call End() ?
        _entities.erase(std::remove(_entities.begin(), _entities.end(), gameObject), _entities.end());
    }

    void Engine::CreateEmptyGameObject()
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
        AddEntity(gameObject);
    }

    GameObject *Engine::GetSelectedEntity() const
    {
        return _selectedEntity;
    }

    void Engine::SetSelectedEntity(GameObject *object)
    {
        _selectedEntity = object;
    }

    GameObject *Engine::GetMainCamera() const
    {
        return _mainCamera;
    }
}