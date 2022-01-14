/*
** EPITECH PROJECT, 2021
** indieStudio
** File description:
** Particle
*/

#include "Particle.hpp"

IS::Particle::Particle(Vector3 position, Vector3 velocity, float gravityEffect, float lifeLenght, float rotation, float scale, ParticleTexturedModel &particleTexturedModel)
{
    _position = position;
    _velocity = velocity;
    _gravityEffect = gravityEffect;
    _lifeLenght = lifeLenght;
    _rotation = rotation;
    _scale = scale;
    _particleTexturedModel = particleTexturedModel;
}

IS::Particle::~Particle()
{
}

Vector3 IS::Particle::getPosition() const
{
    return (_position);
}

Vector3 IS::Particle::getVelocity() const
{
    return (_velocity);
}

float IS::Particle::getGravityEffect() const
{
    return (_gravityEffect);
}

float IS::Particle::getLifeLenght() const
{
    return (_lifeLenght);
}

float IS::Particle::getRotation() const
{
    return (_rotation);
}

float IS::Particle::getScale() const
{
    return (_scale);
}

IS::ParticleTexturedModel IS::Particle::getTexturedModel() const
{
    return (_particleTexturedModel);
}

Vector2 IS::Particle::getTexOffset1() const
{
    return (_texOffset1);
}

Vector2 IS::Particle::getTexOffset2() const
{
    return (_texOffset2);
}

float IS::Particle::getBlendFactor() const
{
    return (_blendFactor);
}

float IS::Particle::getDistanceToCamera() const
{
    return (_distanceToCamera);
}

void IS::Particle::setModelTransform(Matrix &matrix)
{
    _particleTexturedModel.setTransform(matrix);
}


bool IS::Particle::update(Camera3D camera)
{
    _distanceToCamera = std::pow(Vector3Distance(_position, camera.position), 2);
    updateTextureCoordInfo();
    _velocity.y += -GRAVITY * _gravityEffect * GetFrameTime();
    _position.x += _velocity.x * GetFrameTime();
    _position.y += _velocity.y * GetFrameTime();
    _position.z += _velocity.z * GetFrameTime();
    _elapsedTime += GetFrameTime();
    return _elapsedTime < _lifeLenght;
}

void IS::Particle::updateTextureCoordInfo()
{
    float lifeFactor = _elapsedTime / _lifeLenght;
    int stageCount = std::pow(_particleTexturedModel.getNumberOfRows(), 2);
    float atlasProgression = lifeFactor * stageCount;
    int index1 = floor(atlasProgression);
    int index2 = index1 < stageCount - 1 ? index1 + 1: index1;
    _blendFactor = atlasProgression - index1;

    int column1 = index1 % _particleTexturedModel.getNumberOfRows();
    int row1 = index1 / _particleTexturedModel.getNumberOfRows();
    _texOffset1.x = (float) column1 / _particleTexturedModel.getNumberOfRows();
    _texOffset1.y = (float) row1 / _particleTexturedModel.getNumberOfRows();

    int column2 = index2 % _particleTexturedModel.getNumberOfRows();
    int row2 = index2 / _particleTexturedModel.getNumberOfRows();
    _texOffset2.x = (float) column2 / _particleTexturedModel.getNumberOfRows();
    _texOffset2.y = (float) row2 / _particleTexturedModel.getNumberOfRows();
}

bool IS::Particle::operator<(const Particle &other) const
{
    return other.getDistanceToCamera() < _distanceToCamera;
}