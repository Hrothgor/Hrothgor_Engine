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

#define MAX_LIGHTS 100

static int lightsCount = 0;

hr::Light::Light(GameObject *gameObject)
    : Component(gameObject)
    , _locations(LOC_COUNT, -1)
{
    _name = "Light";
    _type = DIRECTIONAL;
    _target = {0, -1, 0};
    _range = 10.0;
    _color = WHITE;
    _intensity = 1;
}

hr::Light::~Light()
{
}

void hr::Light::Update()
{
    Master3DRenderer::Get()->RegisterLight(GetGameObject());
}

void hr::Light::UpdateValues(Shader shader)
{
    if (lightsCount < MAX_LIGHTS && _locations[0] == -1)
    {
        std::string enabledName = "lights[" + std::to_string(lightsCount) + "].enabled";
        std::string typeName = "lights[" + std::to_string(lightsCount) + "].type";
        std::string targetName = "lights[" + std::to_string(lightsCount) + "].target";
        std::string posName = "lights[" + std::to_string(lightsCount) + "].position";
        std::string rangeName = "lights[" + std::to_string(lightsCount) + "].range";
        std::string colorName = "lights[" + std::to_string(lightsCount) + "].color";
        std::string intensityName = "lights[" + std::to_string(lightsCount) + "].intensity";

        _locations[LOC_ENABLED] = GetShaderLocation(shader, enabledName.c_str());
        _locations[LOC_TYPE] = GetShaderLocation(shader, typeName.c_str());
        _locations[LOC_TARGET] = GetShaderLocation(shader, targetName.c_str());
        _locations[LOC_POS] = GetShaderLocation(shader, posName.c_str());
        _locations[LOC_RANGE] = GetShaderLocation(shader, rangeName.c_str());
        _locations[LOC_COLOR] = GetShaderLocation(shader, colorName.c_str());
        _locations[LOC_INTENSITY] = GetShaderLocation(shader, intensityName.c_str());

        lightsCount++;
    }

    if (_locations[0] == -1)
        return;

    int enabled = 1;
    SetShaderValue(shader, _locations[LOC_ENABLED], &enabled, SHADER_UNIFORM_INT);

    SetShaderValue(shader, _locations[LOC_TYPE], &_type, SHADER_UNIFORM_INT);

    float target[3] = {_target.x, _target.y, _target.z};
    SetShaderValue(shader, _locations[LOC_TARGET], &target, SHADER_UNIFORM_VEC3);

    Transform *transform = GetTransform();
    float pos[3] = {transform->GetPosition().x,
                    transform->GetPosition().y,
                    transform->GetPosition().z};
    SetShaderValue(shader, _locations[LOC_POS], &pos, SHADER_UNIFORM_VEC3);

    SetShaderValue(shader, _locations[LOC_RANGE], &_range, SHADER_UNIFORM_FLOAT);

    Vector4 vec = ColorNormalize(_color);
    float color[4] = {vec.x, vec.y, vec.z, vec.w};
    SetShaderValue(shader, _locations[LOC_COLOR], &color, SHADER_UNIFORM_VEC4);

    SetShaderValue(shader, _locations[LOC_INTENSITY], &_intensity, SHADER_UNIFORM_FLOAT);
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