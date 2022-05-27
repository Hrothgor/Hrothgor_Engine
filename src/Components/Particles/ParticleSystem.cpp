/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** ParticleSystem
*/

#include "ParticleSystem.hpp"
#include "RenderEngine/Master3DRenderer.hpp"
#include "RenderEngine/UI/UIElement.hpp"
#include "RenderEngine/AssetsManager.hpp"

#include "Components/Transform.hpp"

#include "EmitParticle.hpp"

namespace hr {
    ParticleSystem::ParticleSystem(GameObject *gameObject)
        : Component(gameObject)
    {
        _name = "ParticleSystem";
        _pps = 10;
        _scale = 1.0;
        _rotation = 0.0;
        _speed = 1.0;
        _gravityModifier = 0.5;
        _lifeLength = 5.0;
        _startColor = WHITE;
        _maxParticle = 1000;
        _emissionType = CONE;
        _coneAngle = 20;
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
            Vector3 dir = EmitParticle::CalcDirection(_emissionType, *GetTransform(), _coneAngle);
            part->SetVelocity(Vector3Scale(dir, _speed));
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

    float ParticleSystem::GetSpeed() const
    {
        return _speed;
    }

    void ParticleSystem::SetSpeed(float speed)
    {
        _speed = speed;
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

    ParticleEmissionType ParticleSystem::GetEmissionType() const
    {
        return _emissionType;
    }

    void ParticleSystem::SetEmissionType(ParticleEmissionType emissionType)
    {
        _emissionType = emissionType;
    }

    float ParticleSystem::GetConeAngle() const
    {
        return _coneAngle;
    }

    void ParticleSystem::SetConeAngle(float coneAngle)
    {
        _coneAngle = coneAngle;
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
        UIElement::FloatField("Scale", [this](){return GetScale();}, [this](float val){SetScale(val);});
        UIElement::FloatField("Rotation", [this](){return GetRotation();}, [this](float val){SetRotation(val);});
        UIElement::FloatField("Speed", [this](){return GetSpeed();}, [this](float val){SetSpeed(val);});
        UIElement::FloatField("Gravity modifier", [this](){return GetGravityModifier();}, [this](float val){SetGravityModifier(val);});
        UIElement::FloatField("Life length", [this](){return GetLifeLength();}, [this](float val){SetLifeLength(val);});
        UIElement::ColorField("Start color", [this](){return GetStartColor();}, [this](Color val){SetStartColor(val);});
        
        UIElement::Header("Texture Values");
        UIElement::TextureField("Texture", [this](){return GetTexturePath();}, [this](const std::string &str){LoadTextureFromPath(str);});
        std::vector<std::string> enumNames = {"Simple", "Atlas"};
        UIElement::EnumField("Texture Type", [this](){return GetTextureType();}, [this](int val){SetTextureType((TextureType)val);}, enumNames);
        switch (_textureType) {
            case SIMPLE:
                break;
            case ATLAS:
                UIElement::IntField("Number of rows", [this](){return GetNumberOfRows();}, [this](int val){SetNumberOfRows(val);});
                break;
        }

        UIElement::Header("Shape Emission");
        enumNames = {"Cone", "Sphere", "Static"};
        UIElement::EnumField("Emission Type", [this](){return GetEmissionType();}, [this](int val){SetEmissionType((ParticleEmissionType)val);}, enumNames);
        switch (_emissionType) {
            case CONE:
                UIElement::FloatField("Cone Angle", [this](){return GetConeAngle();}, [this](float val){SetConeAngle(val);}, 0.2, 1, 89);
                break;
            case SPHERE:
                break;
            case STATIC:
                break;
        }
    }

    void ParticleSystem::OnDrawGizmos()
    {
        Transform *transform = GetTransform();

        switch (_emissionType) {
            case CONE: 
                {
                float hypothenuse = 2;
                float length = cos(_coneAngle * DEG2RAD) * hypothenuse;
                float radius = sin(_coneAngle * DEG2RAD) * hypothenuse;
                DrawCylinderWiresEx(transform->GetPositionWorld(), Vector3Add(GetTransform()->GetPositionWorld(), Vector3Multiply(transform->GetFront(), {length, length, length})),
                            0, radius,
                            8, BLUE);
                }
                break;
            case SPHERE:
                DrawSphereWires(transform->GetPositionWorld(), 2,
                            8, 6, BLUE);
                break;
            case STATIC:
                break;
        }
    }

    nlohmann::json ParticleSystem::ToJson() const
    {
        nlohmann::json json;

        json["pps"] = _pps;
        json["maxParticle"] = _maxParticle;
        json["scale"] = _scale;
        json["rotation"] = _rotation;
        json["speed"] = _speed;
        json["gravityModifier"] = _gravityModifier;
        json["lifeLength"] = _lifeLength;
        json["startColor"] = {_startColor.r, _startColor.g, _startColor.b, _startColor.a};
        json["texturePath"] = _texturePath;
        json["textureType"] = _textureType;
        json["numberOfRows"] = _numberOfRows;
        json["emissionType"] = _emissionType;
        json["coneAngle"] = _coneAngle;

        return json;
    }

    void ParticleSystem::FromJson(const nlohmann::json &json)
    {
        _pps = json["pps"].get<int>();
        _scale = json["scale"].get<float>();
        _rotation = json["rotation"].get<float>();
        _speed = json["speed"].get<float>();
        _gravityModifier = json["gravityModifier"].get<float>();
        _lifeLength = json["lifeLength"].get<float>();
        _startColor = {json["startColor"][0].get<unsigned char>(), json["startColor"][1].get<unsigned char>(), json["startColor"][2].get<unsigned char>(), json["startColor"][3].get<unsigned char>()};
        _texturePath = json["texturePath"].get<std::string>();
        _maxParticle = json["maxParticle"].get<int>();
        _textureType = (TextureType)json["textureType"].get<int>();
        _numberOfRows = json["numberOfRows"].get<int>();
        _emissionType = (ParticleEmissionType)json["emissionType"].get<int>();
        _coneAngle = json["coneAngle"].get<float>();

        LoadTextureFromPath(_texturePath);
    }

    Component *ParticleSystem::Clone(GameObject *gameObject)
    {
        ParticleSystem *ret = new ParticleSystem(gameObject);
        ret->SetPPS(_pps);
        ret->SetScale(_scale);
        ret->SetRotation(_rotation);
        ret->SetSpeed(_speed);
        ret->SetGravityModifier(_gravityModifier);
        ret->SetLifeLength(_lifeLength);
        ret->SetStartColor(_startColor);
        ret->LoadTextureFromPath(_texturePath);
        ret->SetMaxParticle(_maxParticle);
        ret->SetTextureType(_textureType);
        ret->SetNumberOfRows(_numberOfRows);
        ret->SetEmissionType(_emissionType);
        ret->SetConeAngle(_coneAngle);
        return ret;
    }
}