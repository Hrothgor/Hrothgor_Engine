/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** Light
*/

#include "Light.hpp"
#include "../RenderEngine/Master3DRenderer.hpp"
#include "Transform.hpp"
#include "../Ecs/GameObject.hpp"
#include "../RenderEngine/UI/UIElement.hpp"

hr::Light::Light(GameObject *gameObject)
    : Component(gameObject)
{
    _name = "Light";
    _type = DIRECTIONAL;
    _target = Vector3Zero();
    _range = 10.0;
    _color = WHITE;
    _intensity = 1;
}

hr::Light::~Light()
{
}

void hr::Light::Update()
{
    Vector3 rotation = GetTransform()->GetRotation();
    Vector3 front;

    front.x = cos(DEG2RAD * rotation.x) * cos(DEG2RAD * rotation.y);
    front.y = sin(DEG2RAD * rotation.y);
    front.z = sin(DEG2RAD * rotation.x) * cos(DEG2RAD * rotation.y);
    front = Vector3Normalize(front);

    _target = Vector3Add(GetTransform()->GetPosition(), front);

    Master3DRenderer::Get()->RegisterLight(GetGameObject());
}

hr::LightType hr::Light::GetType() const
{
    return _type;
}

void hr::Light::SetType(const LightType &type)
{
    _type = type;
}

Vector3 hr::Light::GetTarget() const
{
    return _target;
}

void hr::Light::SetTarget(const Vector3 &target)
{
    _target = target;
}

float hr::Light::GetRange() const
{
    return _range;
}

void hr::Light::SetRange(const float &range)
{
    _range = range;
}

float hr::Light::GetIntensity() const
{
    return _intensity;
}

void hr::Light::SetIntensity(const float &intensity)
{
    _intensity = intensity;
}

Color hr::Light::GetColor() const
{
    return _color;
}

void hr::Light::SetColor(const Color &color)
{
    _color = color;
}

void hr::Light::ImGuiRender()
{
    UIElement::ColorField("Color", [this](){return GetColor();}, [this](Color col){SetColor(col);});
}