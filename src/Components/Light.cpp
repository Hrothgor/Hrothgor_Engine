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
    _front = Vector3Zero();
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

    _front.x = cos(DEG2RAD * rotation.x) * cos(DEG2RAD * rotation.y);
    _front.y = sin(DEG2RAD * rotation.y);
    _front.z = sin(DEG2RAD * rotation.x) * cos(DEG2RAD * rotation.y);
    _front = Vector3Normalize(_front);

    _target = Vector3Add(GetTransform()->GetPosition(), _front);

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
    UIElement::SliderFloatField("Intensity", [this](){return GetIntensity();}, [this](float val){SetIntensity(val);}, 0, 2);
}

void hr::Light::OnDrawGizmos()
{
    Transform *transform = GetTransform();
    float len = 5;
    DrawCylinderWiresEx(transform->GetPosition(), Vector3Add(GetTransform()->GetPosition(), 
                        Vector3Multiply(_front, {len, len, len})), 1, 2,
                        8, YELLOW);
}