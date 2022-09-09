/*
** EPITECH PROJECT, 2022
** Hrothgor_Engine
** File description:
** ShadowShader
*/

#include "ShadowShader.hpp"

namespace hr {
    ShadowShader::ShadowShader()
        : DefaultShader("Engine/Ressources/Shaders/Shadow.vs", "Engine/Ressources/Shaders/Shadow.fs")
    {
        _locationLightSpaceMatrix = GetShaderLocation(_shader, "lightSpaceMatrix");
    }

    ShadowShader::~ShadowShader()
    {
    }

    void ShadowShader::UpdateLightSpaceMatrix(Matrix mat)
    {
        SetShaderValueMatrix(_shader, _locationLightSpaceMatrix, mat);
    }
}
