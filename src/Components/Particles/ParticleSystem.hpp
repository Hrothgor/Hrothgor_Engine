/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** ParticleSystem
*/

#ifndef PARTICLESYSTEM_HPP_
#define PARTICLESYSTEM_HPP_

#include "Include.hpp"
#include "Ecs/Component.hpp"
#include "Json.hpp"
#include "Particle.hpp"

namespace hr {
    enum ParticleEmissionType {
        CONE,
        SPHERE,
        STATIC
    };

    class ParticleSystem : public Component {
        public:
            ParticleSystem(GameObject *gameObject);
            ~ParticleSystem();

            void Start() override {};
            void Update() override;
            void LateUpdate() override {};
            void UpdateOnSimulation() override {};
            void End() override {};

            int GetPPS() const;
            void SetPPS(int pps);
            float GetScale() const;
            void SetScale(float scale);
            float GetRotation() const;
            void SetRotation(float rotation);
            float GetSpeed() const;
            void SetSpeed(float speed);
            float GetGravityModifier() const;
            void SetGravityModifier(float gravityModifier);
            float GetLifeLength() const;
            void SetLifeLength(float lifeLength);
            Color GetStartColor() const;
            void SetStartColor(Color startColor);
            int GetMaxParticle() const;
            void SetMaxParticle(int maxParticle);
            ParticleEmissionType GetEmissionType() const;
            void SetEmissionType(ParticleEmissionType emissionType);
            float GetConeAngle() const;
            void SetConeAngle(float coneAngle);

            TextureType GetTextureType() const;
            void SetTextureType(TextureType textureType);
            int GetNumberOfRows() const;
            void SetNumberOfRows(int numberOfRows);

            int GetParticleCount() const;
            void DecreaseParticleCount();
            void IncreaseParticleCount();

            Texture2D GetTexture() const;
            std::string GetTexturePath() const;
            void LoadTextureFromPath(const std::string &path);

            void ImGuiRender();
            void OnDrawGizmos();

            virtual nlohmann::json ToJson() const override;
            virtual void FromJson(const nlohmann::json &json) override;

            virtual Component *Clone(GameObject *gameObject) override;
        protected:
        private:
            int _pps;
            float _scale;
            float _rotation;
            float _speed;
            float _gravityModifier;
            float _lifeLength;
            Color _startColor;
            int _maxParticle;

            ParticleEmissionType _emissionType;
            float _coneAngle;

            TextureType _textureType = SIMPLE;
            int _numberOfRows = 1;

            Texture2D _texture = {0};
            std::string _texturePath;

            float _particlesToCreate = 0;
            int _count = 0;
    };
}

#endif /* !PARTICLESYSTEM_HPP_ */