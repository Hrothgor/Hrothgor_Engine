/*
** EPITECH PROJECT, 2022
** Hrothgor_Engine
** File description:
** EmitParticle
*/

#include "EmitParticle.hpp"

namespace hr {
    Vector3 EmitParticle::CalcDirection(ParticleEmissionType type, Transform transform, float coneAngle)
    {
        Vector3 dir = Vector3Zero();

        switch (type) {
            case CONE:
                dir = CalcDirectionCone(transform, coneAngle);
                break;
            case SPHERE:
                dir = CalcDirectionSphere();
                break;
            case STATIC:
                dir = CalcDirectionStatic();
                break;
            default:
                break;
        }
        return dir;
    }

    Vector3 EmitParticle::CalcDirectionCone(Transform transform, float coneAngle)
    {
        Vector3 axis = {1, 0, 0};

        float radius = sin(coneAngle * DEG2RAD);

        float dirX = ((float) rand() / (float) RAND_MAX) * (radius * 2) - radius;
        float dirY = ((float) rand() / (float) RAND_MAX) * (radius * 2) - radius;
        float dirZ = ((float) rand() / (float) RAND_MAX) * (radius * 2) - radius;

        Vector3 dir = { dirX + axis.x, dirY + axis.y, dirZ + axis.z };
        Vector3 rt = transform.GetRotationRadian();
        rt = {rt.x * -1, rt.y, rt.z};
        dir = Vector3Transform(dir, MatrixRotateXYZ(rt));
        dir = Vector3Normalize(dir);
        return dir;
    }

    Vector3 EmitParticle::CalcDirectionSphere()
    {
        float dirX = ((float) rand() / (float) RAND_MAX) * 1 - 0.5;
        float dirY = ((float) rand() / (float) RAND_MAX) * 1 - 0.5;
        float dirZ = ((float) rand() / (float) RAND_MAX) * 1 - 0.5;
        Vector3 dir = { dirX, dirY, dirZ };
        dir = Vector3Normalize(dir);
        return dir;
    }

    Vector3 EmitParticle::CalcDirectionStatic()
    {
        return Vector3Zero();
    }
}