/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** MainCamera3D
*/

#include "MainCamera3D.hpp"
#include "Transform.hpp"

hr::MainCamera3D::MainCamera3D(GameObject *gameObject)
    : Component(gameObject)
{
    _name = "MainCamera3D";
    _camera = { 0 };
    _camera.position = {0, 0, 0};
    _camera.target = { 0.0, 0.0, 0.0 };
    _camera.up = { 0.0, 1.0, 0.0 };
    _camera.fovy = 70;
    _camera.projection = CAMERA_PERSPECTIVE;
    // SetCameraMode(_camera, CAMERA_FIRST_PERSON);
}

hr::MainCamera3D::~MainCamera3D()
{
}

void hr::MainCamera3D::Update()
{
    Transform *transform = GetTransform();
    _camera.position = transform->GetPosition();

    UpdateCamera(&_camera);
}

Camera3D hr::MainCamera3D::GetCamera3D() const
{
    return _camera;
}