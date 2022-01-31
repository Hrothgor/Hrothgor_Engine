/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** MainCamera3D
*/

#include "MainCamera3D.hpp"

Components::MainCamera3D::MainCamera3D(GameObject *gameObject)
    : Component(gameObject)
{
    _camera = { 0 };
    _camera.position = {50, 20, 50};
    _camera.target = { 0.0, 0.0, 0.0 };
    _camera.up = { 0.0, 1.0, 0.0 };
    _camera.fovy = 70;
    _camera.projection = CAMERA_PERSPECTIVE;
    SetCameraMode(_camera, CAMERA_FIRST_PERSON);
}

Components::MainCamera3D::~MainCamera3D()
{
}

void Components::MainCamera3D::Update()
{
    UpdateCamera(&_camera);
}

Camera3D Components::MainCamera3D::GetCamera3D() const
{
    return _camera;
}

