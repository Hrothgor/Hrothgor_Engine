/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** MainCamera3D
*/

#include "MainCamera3D.hpp"
#include "Transform.hpp"
#include "Ecs/GameObject.hpp"

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

        _camera.target = Vector3Add(_camera.position, transform->GetFront());

        UpdateCamera(&_camera);
    }

    void MainCamera3D::UpdateCameraMovement()
    {
        Transform *transform = GetTransform();

        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
            Vector2 mouseDelta = GetMouseDelta();
            Vector3 rotation = transform->GetRotation();
            rotation.y += mouseDelta.x * GetFrameTime() * _turnSpeed;
            rotation.z += mouseDelta.y * GetFrameTime() * _turnSpeed;
            transform->SetRotation(rotation);
        }

        float currentSpeed = 0;
        if (IsKeyDown(KEY_W))
            currentSpeed = _speed;
        if (IsKeyDown(KEY_S))
            currentSpeed = -_speed;
        float dist = currentSpeed * GetFrameTime();
        transform->Translate(Vector3Multiply(transform->GetFront(), {dist, dist, dist}));
    }

    Camera3D MainCamera3D::GetCamera3D() const
    {
        return _camera;
    }

    void MainCamera3D::SetCamera3D(const Camera3D &camera3D)
    {
        _camera = camera3D;
    }

    void MainCamera3D::SetSpeed(float speed)
    {
        _speed = speed;
    }

    void MainCamera3D::SetTurnSpeed(float turnSpeed)
    {
        _turnSpeed = turnSpeed;
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

    Component *MainCamera3D::Clone(GameObject *gameObject)
    {
        MainCamera3D *ret = new MainCamera3D(gameObject);
        ret->SetCamera3D(_camera);
        ret->SetSpeed(_speed);
        ret->SetTurnSpeed(_turnSpeed);
        return ret;
    }
}