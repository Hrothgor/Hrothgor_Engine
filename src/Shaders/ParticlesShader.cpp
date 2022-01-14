/*
** EPITECH PROJECT, 2021
** indieStudio
** File description:
** ParticlesShader
*/

#include "ParticlesShader.hpp"

IS::ParticlesShader::ParticlesShader()
{
    _shader.id = -1;
}

IS::ParticlesShader::~ParticlesShader()
{
}

void IS::ParticlesShader::initShader()
{
    _shader = LoadShader(ASSETS_PATH"ressources/Shaders/particles.vs",
                        ASSETS_PATH"ressources/Shaders/particles.fs");
    loc_texOffset1 = GetShaderLocation(_shader, "texOffset1");
    loc_texOffset2 = GetShaderLocation(_shader, "texOffset2");
    loc_numberOfRows = GetShaderLocation(_shader, "numberOfRows");
    loc_blend = GetShaderLocation(_shader, "blend");
}

void IS::ParticlesShader::loadData(Vector2 texoffset1, Vector2 texoffset2, int numberOfRows, float blend)
{
    SetShaderValueV(_shader, loc_texOffset1, &texoffset1, SHADER_UNIFORM_VEC2, 1);
    SetShaderValueV(_shader, loc_texOffset2, &texoffset2, SHADER_UNIFORM_VEC2, 1);
    SetShaderValue(_shader, loc_numberOfRows, &numberOfRows, SHADER_UNIFORM_INT);
    SetShaderValue(_shader, loc_blend, &blend, SHADER_UNIFORM_FLOAT);
}

Shader IS::ParticlesShader::getShader()
{
    if (_shader.id == -1)
        initShader();
    return (_shader);
}

void IS::ParticlesShader::clean()
{
    if (_shader.id == -1)
        UnloadShader(_shader);
}