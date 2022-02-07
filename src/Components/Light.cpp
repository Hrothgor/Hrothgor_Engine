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

namespace hr {
    Light::Light(GameObject *gameObject)
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

    Light::~Light()
    {
    }

    void Light::Update()
    {
        Vector3 rotation = GetTransform()->GetRotation();

        _front.x = cos(DEG2RAD * rotation.x) * cos(DEG2RAD * rotation.y);
        _front.y = sin(DEG2RAD * rotation.y);
        _front.z = sin(DEG2RAD * rotation.x) * cos(DEG2RAD * rotation.y);
        _front = Vector3Normalize(_front);

        _target = Vector3Add(GetTransform()->GetPositionWorld(), _front);

        Master3DRenderer::Get()->RegisterLight(GetGameObject());
    }

    LightType Light::GetType() const
    {
        return _type;
    }

    void Light::SetType(const LightType &type)
    {
        _type = type;
    }

    Vector3 Light::GetTarget() const
    {
        return _target;
    }

    void Light::SetTarget(const Vector3 &target)
    {
        _target = target;
    }

    float Light::GetRange() const
    {
        return _range;
    }

    void Light::SetRange(const float &range)
    {
        _range = range;
    }

    float Light::GetIntensity() const
    {
        return _intensity;
    }

    void Light::SetIntensity(const float &intensity)
    {
        _intensity = intensity;
    }

    Color Light::GetColor() const
    {
        return _color;
    }

    void Light::SetColor(const Color &color)
    {
        _color = color;
    }

    void Light::ImGuiRender()
    {
        UIElement::ColorField("Color", [this](){return GetColor();}, [this](Color col){SetColor(col);});
        UIElement::SliderFloatField("Intensity", [this](){return GetIntensity();}, [this](float val){SetIntensity(val);}, 0, 2);
    }

    void Light::OnDrawGizmos()
    {
        Transform *transform = GetTransform();
        float len = 5;
        DrawCylinderWiresEx(transform->GetPositionWorld(), Vector3Add(GetTransform()->GetPositionWorld(), 
                            Vector3Multiply(_front, {len, len, len})), 1, 2,
                            8, YELLOW);
    }

    nlohmann::json Light::ToJson() const
    {
        nlohmann::json json;

        json["color"] = {_color.r, _color.g, _color.b, _color.a};
        json["intensity"] = _intensity;

        return json;
    }

    void Light::FromJson(const nlohmann::json &json)
    {
        _color = {json["color"][0].get<unsigned char>(), json["color"][1].get<unsigned char>(), json["color"][2].get<unsigned char>(), json["color"][3].get<unsigned char>()};
        _intensity = json["intensity"].get<float>();
    }
}