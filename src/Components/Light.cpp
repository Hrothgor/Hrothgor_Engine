/*
** EPITECH PROJECT, 2022
** Hrothgor_Engine
** File description:
** Light
*/

#include "Light.hpp"
#include "RenderEngine/Master3DRenderer.hpp"
#include "Transform.hpp"
#include "Ecs/GameObject.hpp"
#include "RenderEngine/UI/UIElement.hpp"
#include "Tools/SaveLoad/JsonManager.hpp"

namespace hr {
    Light::Light(GameObject *gameObject)
        : Component(gameObject)
    {
        _name = "Light";
        _type = POINT;
        _target = Vector3Zero();
        _range = 10.0;
        _color = WHITE;
        _intensity = 1;
    }

    Light::~Light()
    {
    }

    void Light::Update()
    {
        _target = GetTransform()->GetPositionWorld() + GetTransform()->GetFront();

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
        std::vector<std::string> enumNames = {"Directional", "Point"};
        UIElement::EnumField("Type", [this](){return GetType();}, [this](int val){SetType((LightType)val);}, enumNames);
        switch (_type) {
            case DIRECTIONAL:
                break;
            case POINT:
                UIElement::FloatField("Range", [this](){return GetRange();}, [this](int val){SetRange(val);}, 1, 0, 5000);
                break;
        }
        UIElement::ColorField("Color", [this](){return GetColor();}, [this](Color col){SetColor(col);});
        UIElement::SliderFloatField("Intensity", [this](){return GetIntensity();}, [this](float val){SetIntensity(val);}, 0, 2);
    }

    void Light::OnDrawGizmos()
    {
        Transform *transform = GetTransform();

        switch (_type) {
            case DIRECTIONAL:
                DrawCylinderWiresEx(transform->GetPositionWorld(), GetTransform()->GetPositionWorld() + Vector3Multiply(transform->GetFront(), {5, 5, 5}),
                            1, 2,
                            8, YELLOW);
                break;
            case POINT:
                DrawSphereWires(transform->GetPositionWorld(), _range,
                            10, 10, YELLOW);
                break;
        }
    }

    nlohmann::json Light::ToJson() const
    {
        nlohmann::json json;

        JsonManager::SaveInt(json, "type", (int)_type);
        JsonManager::SaveFloat(json, "range", _range);
        JsonManager::SaveColor(json, "color", _color);
        JsonManager::SaveFloat(json, "intensity", _intensity);

        return json;
    }

    void Light::FromJson(const nlohmann::json &json)
    {
        _type = (LightType) JsonManager::LoadInt(json, "type");
        _range = JsonManager::LoadFloat(json, "range");
        _color = JsonManager::LoadColor(json, "color");
        _intensity = JsonManager::LoadFloat(json, "intensity");
    }

    Component *Light::Clone(GameObject *gameObject)
    {
        Light *ret = new Light(gameObject);
        ret->SetType(_type);
        ret->SetTarget(_target);
        ret->SetRange(_range);
        ret->SetColor(_color);
        ret->SetIntensity(_intensity);
        return ret;
    }
}