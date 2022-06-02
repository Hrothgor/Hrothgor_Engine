/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** Engine
*/

#include "Engine.hpp"
#include "RenderEngine/DisplayManager.hpp"
#include "PhysicsEngine/PhysicsWorld.hpp"
#include "Tools/SaveLoad/SaveSystem.hpp"
#include "Tools/SaveLoad/LoadSystem.hpp"

#include "Components/MeshRenderer.hpp"
#include "Components/MainCamera3D.hpp"
#include "Components/Transform.hpp"
#include "Components/Light.hpp"

#include "SharedLibrary/LibraryManager.hpp"

namespace hr {
    Engine *Engine::instance = nullptr;

    Engine::Engine()
    {
        SetTraceLogLevel(TraceLogLevel::LOG_WARNING);
        InitWindow(0, 0, "Physics Engine");
        rlImGuiSetup(true);
        ToggleFullscreen();
        InitAudioDevice();
        
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking

        _mainCamera = new GameObject();
        _mainCamera->SetName("mainCamera");
        _mainCamera->AddComponent<MainCamera3D>();
        _mainCamera->GetTransform()->SetPosition(20, 20, 50);
        _mainCamera->GetTransform()->SetRotation(0, 90, 0);
    }

    Engine::~Engine()
    {
    }

    void Engine::Start()
    {
        SetSelectedEntity(nullptr);
        DisplayManager::Get()->Start();
        _mainCamera->Start();
        std::vector<GameObject *> cpy = _entities;
        for (auto ent : cpy)
            if (ent->GetParent() == nullptr)
                ent->Start();
    }

    void Engine::Update()
    {
        LibraryManager libraryManagerTest;
        while (!WindowShouldClose() && _running)
        {
            // TODO Remove this
            if (IsKeyPressed(KEY_O))
                libraryManagerTest.LoadComponent("./libcomponents.so")->UpdateOnSimulation();
            //
            // TODO Remove this
            if (IsKeyPressed(KEY_SPACE))
                SetSimulating(!_simulating);
            if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_D) && _selectedEntity)
                Instantiate(_selectedEntity);
            //
            BeginDrawing();
            {
                {
                    _mainCamera->Update();
                    std::vector<GameObject *> cpy = _entities;
                    for (auto ent : cpy)
                        if (ent->GetParent() == nullptr)
                                ent->Update();
                }
                {
                    _mainCamera->LateUpdate();
                    std::vector<GameObject *> cpy = _entities;
                    for (auto ent : cpy)
                        if (ent->GetParent() == nullptr)
                            ent->LateUpdate();
                }
                {
                    if (_simulating) {
                        _mainCamera->UpdateOnSimulation();
                        std::vector<GameObject *> cpy = _entities;
                        for (auto ent : cpy)
                            if (ent->GetParent() == nullptr)
                                ent->UpdateOnSimulation();
                        PhysicsWorld::Get()->Update();
                    }
                }
                DisplayManager::Get()->Clear(DARKGRAY);
                DisplayManager::Get()->Draw();
            }
            EndDrawing();
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
        (void)parent;
        GameObject *newEnt = object->Clone();
        for (auto child : object->GetChilds()) {
            GameObject *newChild = child->Clone();
            newEnt->AddChild(newChild);
            _entities.push_back(newChild);
        }
        _entities.push_back(newEnt);
        return newEnt;
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
        // TODO NEED THREAD !
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

    std::string Engine::GetProjectName() const
    {
        return _projectName;
    }

    void Engine::SetProjectName(const std::string &projectName)
    {
        _projectName = projectName;
    }
    
    void Engine::SetRunning(bool running)
    {
        _running = running;
    }

    void Engine::SetSimulating(bool simulating)
    {
        if (_simulating == simulating)
            return;
        _simulating = simulating;
        if (_simulating) {
            SetSelectedEntity(nullptr);
            std::vector<GameObject *> rootEntities = GetRootEntities();
            for (auto ent : rootEntities) {
                GameObject *newEnt = ent->Clone();
                for (auto child : ent->GetChilds()) {
                    GameObject *newChild = child->Clone();
                    newEnt->AddChild(newChild);
                    _savedEntities.push_back(newChild);
                }
                _savedEntities.push_back(newEnt);
            }
        } else {
            SetSelectedEntity(nullptr);
            _entities = _savedEntities;
            _savedEntities.clear();
        }
    }
}