/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** MainCamera3D
*/

#include "MainCamera3D.hpp"
#include "Transform.hpp"
#include "../Ecs/GameObject.hpp"

namespace hr {
    MainCamera3D::MainCamera3D(GameObject *gameObject)
        : Component(gameObject)
    {
        _name = "MainCamera3D";
        _camera = { 0 };
        _camera.position = {0, 0, 0};
        _camera.target = { 0.0, 0.0, 0.0 };
        _camera.up = { 0.0, 1.0, 0.0 };
        _camera.fovy = 60;
        _camera.projection = CAMERA_PERSPECTIVE;
        SetCameraMode(_camera, CAMERA_CUSTOM);
    }

    MainCamera3D::~MainCamera3D()
    {
    }

    void MainCamera3D::Update()
    {
        Transform *transform = GetTransform();
        _camera.position = transform->GetPositionWorld();

        Vector3 rotation = GetTransform()->GetRotation();
        Vector3 front;
        front.x = cos(DEG2RAD * rotation.x) * cos(DEG2RAD * rotation.y);
        front.y = sin(DEG2RAD * rotation.y);
        front.z = sin(DEG2RAD * rotation.x) * cos(DEG2RAD * rotation.y);
        front = Vector3Normalize(front);
        _camera.target = Vector3Add(_camera.position, front);

        UpdateCamera(&_camera);
    }

    void MainCamera3D::UpdateCameraMovement()
    {
        Transform *transform = GetTransform();

        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
            Vector2 mouseDelta = GetMouseDelta();
            Vector3 rotation = transform->GetRotation();
            rotation.x -= mouseDelta.x * GetFrameTime() * 20;
            rotation.y += mouseDelta.y * GetFrameTime() * 20;
            transform->SetRotation(rotation);
        }

        if (IsKeyDown(KEY_W))
            transform->Translate({0, 0, -20 * GetFrameTime()});
        if (IsKeyDown(KEY_A))
            transform->Translate({-20 * GetFrameTime(), 0, 0});
        if (IsKeyDown(KEY_S))
            transform->Translate({0, 0, 20 * GetFrameTime()});
        if (IsKeyDown(KEY_D))
            transform->Translate({20 * GetFrameTime(), 0, 0});
    }

    Camera3D MainCamera3D::GetCamera3D() const
    {
        return _camera;
    }

    nlohmann::json MainCamera3D::ToJson() const
    {
        nlohmann::json json;

        return json;
    }

    void MainCamera3D::FromJson(const nlohmann::json &json)
    {
        (void)json;
    }
}