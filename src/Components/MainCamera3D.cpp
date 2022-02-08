/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** MainCamera3D
*/

#include "MainCamera3D.hpp"
#include "Transform.hpp"

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
        // SetCameraMode(_camera, CAMERA_FIRST_PERSON);
    }

    MainCamera3D::~MainCamera3D()
    {
    }

    void MainCamera3D::Update()
    {
        Transform *transform = GetTransform();
        _camera.position = transform->GetPositionWorld();

        UpdateCamera(&_camera);
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