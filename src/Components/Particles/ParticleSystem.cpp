/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** ParticleSystem
*/

#include "ParticleSystem.hpp"
#include "../../RenderEngine/Master3DRenderer.hpp"
#include "../../RenderEngine/UI/UIElement.hpp"
#include "../../RenderEngine/AssetsManager.hpp"

#include "../Transform.hpp"

namespace hr {
    ParticleSystem::ParticleSystem(GameObject *gameObject)
        : Component(gameObject)
    {
        _name = "ParticleSystem";
        _pps = 10;
        _velocity = {0, 10, 0};
        _gravityModifier = 0.5;
        _lifeLength = 5.0;
        _scale = 1.0;
        _rotation = 0.0;
        _startColor = WHITE;
        _maxParticle = 1000;
    }

    ParticleSystem::~ParticleSystem()
    {
    }

    void ParticleSystem::Update()
    {
        _particlesToCreate += _pps * GetFrameTime();
        if (_particlesToCreate < 1)
            return;
        int count = floor(_particlesToCreate);
        _particlesToCreate -= count;
        for (int i = 0; i < count; i++) {
            if (_count >= _maxParticle)
                break;
            Transform transform(nullptr);
            transform.SetPosition(GetTransform()->GetPositionWorld());
            transform.SetScale({_scale, _scale, _scale});
            Particle *part = new Particle(this);
            part->SetTransform(transform);
            part->SetVelocity(_velocity);
            part->SetGravityModifier(_gravityModifier);
            part->SetLifeLength(_lifeLength);
            part->SetStartColor(_startColor);
            part->SetTexture(_texture);
            part->SetTextureType(_textureType);
            part->SetNumberOfRows(_numberOfRows);
            Master3DRenderer::Get()->RegisterParticle(part);
        }
    }

    int ParticleSystem::GetPPS() const
    {
        return _pps;
    }

    void ParticleSystem::SetPPS(int pps)
    {
        _pps = pps;
    }

    Vector3 ParticleSystem::GetVelocity() const
    {
        return _velocity;
    }

    void ParticleSystem::SetVelocity(Vector3 velocity)
    {
        _velocity = velocity;
    }

    float ParticleSystem::GetGravityModifier() const
    {
        return _gravityModifier;
    }

    void ParticleSystem::SetGravityModifier(float gravityModifier)
    {
        _gravityModifier = gravityModifier;
    }

    float ParticleSystem::GetLifeLength() const
    {
        return _lifeLength;
    }

    void ParticleSystem::SetLifeLength(float lifeLength)
    {
        _lifeLength = lifeLength;
    }

    float ParticleSystem::GetScale() const
    {
        return _scale;
    }

    void ParticleSystem::SetScale(float scale)
    {
        _scale = scale;
    }

    float ParticleSystem::GetRotation() const
    {
        return _rotation;
    }

    void ParticleSystem::SetRotation(float rotation)
    {
        _rotation = rotation;
    }

    Color ParticleSystem::GetStartColor() const
    {
        return _startColor;
    }

    void ParticleSystem::SetStartColor(Color startColor)
    {
        _startColor = startColor;
    }

    void ParticleSystem::LoadTextureFromPath(const std::string &path)
    {
        if (AssetsManager::Get()->TextureContains(path)) {
            _texturePath = path;
            _texture = AssetsManager::Get()->GetTexture(path);
        }
    }

    int ParticleSystem::GetMaxParticle() const
    {
        return _maxParticle;
    }

    void ParticleSystem::SetMaxParticle(int maxParticle)
    {
        _maxParticle = maxParticle;
    }

    TextureType ParticleSystem::GetTextureType() const
    {
        return _textureType;
    }

    void ParticleSystem::SetTextureType(TextureType textureType)
    {
        _textureType = textureType;
    }

    int ParticleSystem::GetNumberOfRows() const
    {
        return _numberOfRows;
    }

    void ParticleSystem::SetNumberOfRows(int numberOfRows)
    {
        _numberOfRows = numberOfRows;
    }

    int ParticleSystem::GetParticleCount() const
    {
        return _count;
    }

    void ParticleSystem::DecreaseParticleCount()
    {
        if (_count > 0)
            _count--;
    }

    void ParticleSystem::IncreaseParticleCount()
    {
        if (_count < _maxParticle)
            _count++;
    }

    Texture2D ParticleSystem::GetTexture() const
    {
        return _texture;
    }

    std::string ParticleSystem::GetTexturePath() const
    {
        return _texturePath;
    }

    void ParticleSystem::ImGuiRender()
    {
        UIElement::Header("System Values");
        UIElement::IntField("Particles per second", [this](){return GetPPS();}, [this](int val){SetPPS(val);});
        UIElement::IntField("Max particle", [this](){return GetMaxParticle();}, [this](int val){SetMaxParticle(val);});
        UIElement::Header("Particles Values");
        UIElement::Vector3Field("Velocity", [this](){return GetVelocity();}, [this](Vector3 val){SetVelocity(val);});
        UIElement::FloatField("Gravity modifier", [this](){return GetGravityModifier();}, [this](float val){SetGravityModifier(val);});
        UIElement::FloatField("Life length", [this](){return GetLifeLength();}, [this](float val){SetLifeLength(val);});
        UIElement::FloatField("Scale", [this](){return GetScale();}, [this](float val){SetScale(val);});
        UIElement::FloatField("Rotation", [this](){return GetRotation();}, [this](float val){SetRotation(val);});
        UIElement::ColorField("Start color", [this](){return GetStartColor();}, [this](Color val){SetStartColor(val);});
        UIElement::Header("Texture Values");
        UIElement::TextureField("Texture", [this](){return GetTexturePath();}, [this](const std::string &str){LoadTextureFromPath(str);});
        std::vector<std::string> enumNames = {"Simple", "Atlas"};
        UIElement::EnumField("TextureType", [this](){return GetTextureType();}, [this](int val){SetTextureType((TextureType)val);}, enumNames);
        switch (_textureType) {
            case SIMPLE:
                break;
            case ATLAS:
                UIElement::IntField("Number of rows", [this](){return GetNumberOfRows();}, [this](int val){SetNumberOfRows(val);});
                break;
        }
    }

    nlohmann::json ParticleSystem::ToJson() const
    {
        nlohmann::json json;

        json["pps"] = _pps;
        json["velocity"] = {_velocity.x, _velocity.y, _velocity.z};
        json["gravityModifier"] = _gravityModifier;
        json["lifeLength"] = _lifeLength;
        json["scale"] = _scale;
        json["rotation"] = _rotation;
        json["startColor"] = {_startColor.r, _startColor.g, _startColor.b, _startColor.a};
        json["texturePath"] = _texturePath;
        json["maxParticle"] = _maxParticle;
        json["textureType"] = _textureType;
        json["numberOfRows"] = _numberOfRows;

        return json;
    }

    void ParticleSystem::FromJson(const nlohmann::json &json)
    {
        _pps = json["pps"].get<int>();
        _velocity = {json["velocity"][0].get<float>(), json["velocity"][1].get<float>(), json["velocity"][2].get<float>()};
        _gravityModifier = json["gravityModifier"].get<float>();
        _lifeLength = json["lifeLength"].get<float>();
        _scale = json["scale"].get<float>();
        _rotation = json["rotation"].get<float>();
        _startColor = {json["startColor"][0].get<unsigned char>(), json["startColor"][1].get<unsigned char>(), json["startColor"][2].get<unsigned char>(), json["startColor"][3].get<unsigned char>()};
        _texturePath = json["texturePath"].get<std::string>();
        _maxParticle = json["maxParticle"].get<int>();
        _textureType = (TextureType)json["textureType"].get<int>();
        _numberOfRows = json["numberOfRows"].get<int>();

        LoadTextureFromPath(_texturePath);
    }

    Component *ParticleSystem::Clone(GameObject *gameObject)
    {
        ParticleSystem *ret = new ParticleSystem(gameObject);
        ret->SetPPS(_pps);
        ret->SetVelocity(_velocity);
        ret->SetGravityModifier(_gravityModifier);
        ret->SetLifeLength(_lifeLength);
        ret->SetScale(_scale);
        ret->SetRotation(_rotation);
        ret->SetStartColor(_startColor);
        ret->LoadTextureFromPath(_texturePath);
        ret->SetMaxParticle(_maxParticle);
        ret->SetTextureType(_textureType);
        ret->SetNumberOfRows(_numberOfRows);
        return ret;
    }
}