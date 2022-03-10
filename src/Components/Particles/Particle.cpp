/*
** EPITECH PROJECT, 2021
** indieStudio
** File description:
** Particle
*/

#include "Particle.hpp"
#include "../../Tools/GenMesh.hpp"

namespace hr {
    static Mesh particleMesh = {0};

    Particle::Particle(const Transform &transform, const Vector3 &velocity, const float &gravityModifier, const float &lifeLenght, const Texture &texture, const Color &startColor)
        : _transform(transform)
    {
        if (particleMesh.vaoId == 0)
            particleMesh = GenMesh::GenMeshSquare(0.5);
        _velocity = velocity;
        _gravityModifier = gravityModifier;
        _lifeLenght = lifeLenght;
        _texture = texture;
        _startColor = startColor;
        _mesh = particleMesh;
    }

    Particle::~Particle()
    {
    }

    bool Particle::Update(Camera3D camera)
    {
        _elapsedTime += GetFrameTime();
        if (_elapsedTime > _lifeLenght)
            return false;
        if (_textureType == ATLAS)
            UpdateTextureCoordInfo();
        _velocity.y += -9.81 * _gravityModifier * GetFrameTime();
        _transform.Translate(Vector3Scale(_velocity, GetFrameTime()));
        _distanceToCamera = std::pow(Vector3Distance(_transform.GetPosition(), camera.position), 2);
        RotateTowardCamera(camera);
        return true;
    }

    void Particle::RotateTowardCamera(Camera3D camera)
    {
        // Vector3 direction = Vector3Subtract(_transform.GetPosition(), camera.position);
        // direction = Vector3Normalize(direction);
        // _transform.SetRotation(Vector3Scale(direction, 360));
    }

    void Particle::UpdateTextureCoordInfo()
    {
        float lifeFactor = _elapsedTime / _lifeLenght;
        int stageCount = std::pow(_numberOfRows, 2);
        float atlasProgression = lifeFactor * stageCount;
        int index1 = floor(atlasProgression);
        int index2 = index1 < stageCount - 1 ? index1 + 1: index1;
        _blendFactor = atlasProgression - index1;

        int column1 = index1 % _numberOfRows;
        int row1 = index1 / _numberOfRows;
        _texOffset1.x = (float) column1 / _numberOfRows;
        _texOffset1.y = (float) row1 / _numberOfRows;

        int column2 = index2 % _numberOfRows;
        int row2 = index2 / _numberOfRows;
        _texOffset2.x = (float) column2 / _numberOfRows;
        _texOffset2.y = (float) row2 / _numberOfRows;
    }

    Transform Particle::GetTransform() const
    {
        return _transform;
    }

    Vector3 Particle::GetVelocity() const
    {
        return _velocity;
    }

    float Particle::GetGravityModifier() const
    {
        return _gravityModifier;
    }

    float Particle::GetLifeLenght() const
    {
        return _lifeLenght;
    }

    Color Particle::GetStartColor() const
    {
        return _startColor;
    }

    float Particle::GetDistanceToCamera() const
    {
        return _distanceToCamera;
    }

    Mesh Particle::GetMesh() const
    {
        return _mesh;
    }

    Texture Particle::GetTexture() const
    {
        return _texture;
    }

    TextureType Particle::GetTextureType() const
    {
        return _textureType;
    }

    Vector2 Particle::GetTexOffset1() const
    {
        return _texOffset1;
    }

    Vector2 Particle::GetTexOffset2() const
    {
        return _texOffset2;
    }

    float Particle::GetBlendFactor() const
    {
        return _blendFactor;
    }

    bool Particle::operator<(const Particle &other) const
    {
        return other.GetDistanceToCamera() < _distanceToCamera;
    }
}