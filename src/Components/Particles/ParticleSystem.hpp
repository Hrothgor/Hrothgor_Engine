/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** ParticleSystem
*/

#ifndef PARTICLESYSTEM_HPP_
#define PARTICLESYSTEM_HPP_

#include "include.hpp"
#include "../../Ecs/Component.hpp"
#include "json.hpp"

namespace hr {
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
            Vector3 GetVelocity() const;
            void SetVelocity(Vector3 velocity);
            float GetGravityModifier() const;
            void SetGravityModifier(float gravityModifier);
            float GetLifeLength() const;
            void SetLifeLength(float lifeLength);
            float GetScale() const;
            void SetScale(float scale);
            float GetRotation() const;
            void SetRotation(float rotation);
            Color GetStartColor() const;
            void SetStartColor(Color startColor);
            int GetMaxParticle() const;
            void SetMaxParticle(int maxParticle);

            int GetParticleCount() const;
            void DecreaseParticleCount();
            void IncreaseParticleCount();

            Texture2D GetTexture() const;
            std::string GetTexturePath() const;
            void LoadTextureFromPath(const std::string &path);

            void ImGuiRender();
            void OnDrawGizmos() {};

            virtual nlohmann::json ToJson() const override;
            virtual void FromJson(const nlohmann::json &json) override;

            virtual Component *Clone(GameObject *gameObject) override;
        protected:
        private:
            int _pps;
            Vector3 _velocity;
            float _gravityModifier;
            float _lifeLength;
            float _scale;
            float _rotation;
            Color _startColor;
            int _maxParticle;

            Texture2D _texture = {0};
            std::string _texturePath;

            float _particlesToCreate = 0;
            int _count = 0;
    };
}

#endif /* !PARTICLESYSTEM_HPP_ */