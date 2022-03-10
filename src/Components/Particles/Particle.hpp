/*
** EPITECH PROJECT, 2021
** indieStudio
** File description:
** Particle
*/

#ifndef PARTICLE_HPP_
#define PARTICLE_HPP_

#include "include.hpp"
#include "../Transform.hpp"

namespace hr {
    enum TextureType {
        SIMPLE = 0,
        ATLAS,
    };

    class Particle {
        public:
            Particle(const Transform &transform, const Vector3 &velocity, const float &gravityModifier, const float &lifeLenght, const Texture &texture, const Color &startColor);
            ~Particle();

            bool Update(Camera3D camera);
            void RotateTowardCamera(Camera3D camera);
            void UpdateTextureCoordInfo();

            Transform GetTransform() const;
            Vector3 GetVelocity() const;
            float GetGravityModifier() const;
            float GetLifeLenght() const;
            Color GetStartColor() const;

            float GetDistanceToCamera() const;

            Mesh GetMesh() const;
            Texture GetTexture() const;
            TextureType GetTextureType() const;

            Vector2 GetTexOffset1() const;
            Vector2 GetTexOffset2() const;
            float GetBlendFactor() const;

            bool operator<(const Particle &other) const;

        protected:
        private:
            Transform _transform;
            Vector3 _velocity;
            float _gravityModifier;
            float _lifeLenght;
            Color _startColor;

            float _elapsedTime = 0;
            float _distanceToCamera = 0;
            
            Mesh _mesh = {0};
            Texture _texture = {0};
            int _numberOfRows = 1;
            TextureType _textureType = SIMPLE;
            // Atlas
            Vector2 _texOffset1 = {0};
            Vector2 _texOffset2 = {0};
            float _blendFactor = 0;
    };
}

#endif /* !PARTICLE_HPP_ */
