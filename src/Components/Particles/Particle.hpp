/*
** EPITECH PROJECT, 2021
** indieStudio
** File description:
** Particle
*/

#ifndef PARTICLE_HPP_
#define PARTICLE_HPP_

#include "Include.hpp"
#include "Components/Transform.hpp"

namespace hr {
    class ParticleSystem;

    enum TextureType {
        SIMPLE = 0,
        ATLAS,
    };

    class Particle {
        public:
            Particle(ParticleSystem *parent);
            ~Particle();

            bool Update(Camera3D camera);
            void updateTextureCoordInfo();
            void RotateTowardCamera(Camera3D camera);

            Transform GetTransform() const;
            void SetTransform(const Transform &transform);
            Vector3 GetVelocity() const;
            void SetVelocity(const Vector3 &velocity);
            float GetGravityModifier() const;
            void SetGravityModifier(const float &gravityModifier);
            float GetLifeLength() const;
            void SetLifeLength(const float &lifeLength);
            Color GetStartColor() const;
            void SetStartColor(const Color &startColor);
            TextureType GetTextureType() const;
            void SetTextureType(const TextureType &textureType);
            int GetNumberOfRows() const;
            void SetNumberOfRows(const int &numberOfRows);

            ParticleSystem *GetParentSystem() const;

            float GetDistanceToCamera() const;

            Mesh GetMesh() const;
            Texture GetTexture() const;
            void SetTexture(const Texture &texture);

            Vector2 GetTexOffset1() const;
            Vector2 GetTexOffset2() const;
            float GetBlendFactor() const;

            Matrix GetBillboardMatrix() const;

            float GetElapsedTime() const;

            bool operator<(const Particle &other) const;

        protected:
        private:
            Transform _transform;
            Vector3 _velocity;
            float _gravityModifier;
            float _lifeLength;
            Color _startColor;
            TextureType _textureType = SIMPLE;
            int _numberOfRows = 1;

            float _elapsedTime = 0;
            float _distanceToCamera = 0;
            
            Mesh _mesh = {0};
            Texture _texture = {0};

            Vector2 _texOffset1 = {0};
            Vector2 _texOffset2 = {0};
            float _blendFactor = 0;
            
            Matrix _billboardMatrix;

            ParticleSystem *_parent = nullptr;
    };
}

#endif /* !PARTICLE_HPP_ */
