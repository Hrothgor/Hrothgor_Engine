/*
** EPITECH PROJECT, 2021
** 3D
** File description:
** RigidBody
*/

#include "RigidBody.hpp"

IS::RigidBody::RigidBody()
{
}

IS::RigidBody::~RigidBody()
{
}

Vector3 IS::RigidBody::getVelocity() const
{
    return (_velocity);
}

void IS::RigidBody::setVelocity(Vector3 velocity)
{
    _velocity = velocity;
}

void IS::RigidBody::setVelocity(float x, float y, float z)
{
    _velocity.x = x;
    _velocity.y = y;
    _velocity.z = z;
}

Vector3 IS::RigidBody::getForce() const
{
    return (_force);
}

void IS::RigidBody::setForce(Vector3 force)
{
    _force = force;
}

void IS::RigidBody::setForce(float x, float y, float z)
{
    _force.x = x;
    _force.y = y;
    _force.z = z;
}

float IS::RigidBody::getMass() const
{
    return (_mass);
}

void IS::RigidBody::setMass(float mass)
{
    _mass = mass;
}