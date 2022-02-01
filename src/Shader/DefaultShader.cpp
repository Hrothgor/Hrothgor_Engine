/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** DefaultShader
*/

#include "DefaultShader.hpp"

hr::DefaultShader::DefaultShader(const std::string &pathVs, const std::string &pathFs)
{
    _shader = LoadShader(pathVs.c_str(), pathFs.c_str());
}

hr::DefaultShader::~DefaultShader()
{
}

void hr::DefaultShader::Start()
{
}

void hr::DefaultShader::End()
{
    UnloadShader(_shader);
}

Shader hr::DefaultShader::GetShader() const
{
    return _shader;
}