/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** LightShader
*/

#include "LightShader.hpp"
#include "../Components/Light.hpp"

hr::LightShader::LightShader()
    : DefaultShader("ressources/Shaders/Light.vs", "ressources/Shaders/Light.fs")
{
    int ambientLoc = GetShaderLocation(_shader, "ambient");
    float ambientValue[4] =  { 0.1, 0.1, 0.1, 1.0 };
    SetShaderValue(_shader, ambientLoc, &ambientValue, SHADER_UNIFORM_VEC4);
}

hr::LightShader::~LightShader()
{
}

void hr::LightShader::UpdateCameraLoc(Camera3D camera)
{
    float cameraPos[3] = { camera.position.x, camera.position.y, camera.position.z };
    SetShaderValue(_shader, _shader.locs[SHADER_LOC_VECTOR_VIEW], cameraPos, SHADER_UNIFORM_VEC3);
}