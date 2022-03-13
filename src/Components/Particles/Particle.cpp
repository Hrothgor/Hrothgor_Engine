/*
** EPITECH PROJECT, 2021
** indieStudio
** File description:
** Particle
*/

#include "Particle.hpp"
#include "../../Tools/GenMesh.hpp"
#include "ParticleSystem.hpp"

namespace hr {
    static Mesh particleMesh = {0};

    Particle::Particle(ParticleSystem *parent)
        : _transform(nullptr)
    {
        _parent = parent;
        _parent->IncreaseParticleCount();
        if (particleMesh.vaoId == 0)
            particleMesh = GenMesh::GenMeshSquare(0.5);
        _mesh = particleMesh;
        _billboardMatrix = MatrixIdentity();
    }

    Particle::~Particle()
    {
    }

    bool Particle::Update(Camera3D camera)
    {
        if (_parent == nullptr)
            return false;
        _elapsedTime += GetFrameTime();
        if (_elapsedTime > _lifeLength) {
            _parent->DecreaseParticleCount();
            return false;
        }
        _velocity.y += -9.81 * _gravityModifier * GetFrameTime();
        _transform.Translate(Vector3Scale(_velocity, GetFrameTime()));
        _distanceToCamera = std::pow(Vector3Distance(_transform.GetPosition(), camera.position), 2);
        RotateTowardCamera(camera);
        return true;
    }

    void Particle::RotateTowardCamera(Camera3D camera)
    {
        Matrix viewMatrix = GetCameraMatrix(camera);
        
        _billboardMatrix.m0 = viewMatrix.m0;
        _billboardMatrix.m1 = viewMatrix.m4;
        _billboardMatrix.m2 = viewMatrix.m8;
        _billboardMatrix.m3 = 0;
        _billboardMatrix.m4 = viewMatrix.m1;
        _billboardMatrix.m5 = viewMatrix.m5;
        _billboardMatrix.m6 = viewMatrix.m9;
        _billboardMatrix.m7 = 0;
        _billboardMatrix.m8 = viewMatrix.m2;
        _billboardMatrix.m9 = viewMatrix.m6;
        _billboardMatrix.m10 = viewMatrix.m10;
        _billboardMatrix.m11 = 0;
    }

    Transform Particle::GetTransform() const
    {
        return _transform;
    }

    void Particle::SetTransform(const Transform &transform)
    {
        _transform = transform;
    }

    Vector3 Particle::GetVelocity() const
    {
        return _velocity;
    }

    void Particle::SetVelocity(const Vector3 &velocity)
    {
        _velocity = velocity;
    }

    float Particle::GetGravityModifier() const
    {
        return _gravityModifier;
    }

    void Particle::SetGravityModifier(const float &gravityModifier)
    {
        _gravityModifier = gravityModifier;
    }

    float Particle::GetLifeLength() const
    {
        return _lifeLength;
    }

    void Particle::SetLifeLength(const float &lifeLength)
    {
        _lifeLength = lifeLength;
    }

    Color Particle::GetStartColor() const
    {
        return _startColor;
    }

    void Particle::SetStartColor(const Color &startColor)
    {
        _startColor = startColor;
    }

    TextureType Particle::GetTextureType() const
    {
        return _textureType;
    }

    void Particle::SetTextureType(const TextureType &textureType)
    {
        _textureType = textureType;
    }

    int Particle::GetNumberOfRows() const
    {
        return _numberOfRows;
    }

    void Particle::SetNumberOfRows(const int &numberOfRows)
    {
        _numberOfRows = numberOfRows;
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

    void Particle::SetTexture(const Texture &texture)
    {
        _texture = texture;
    }

    Matrix Particle::GetBillboardMatrix() const
    {
        return _billboardMatrix;
    }

    float Particle::GetElapsedTime() const
    {
        return _elapsedTime;
    }

    bool Particle::operator<(const Particle &other) const
    {
        return other.GetDistanceToCamera() < _distanceToCamera;
    }
}