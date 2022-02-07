/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** DefaultShader
*/

#include "DefaultShader.hpp"

namespace hr {
    DefaultShader::DefaultShader(const std::string &pathVs, const std::string &pathFs)
    {
        _shader = LoadShader(pathVs.c_str(), pathFs.c_str());
    }

    DefaultShader::~DefaultShader()
    {
    }

    void DefaultShader::Start()
    {
    }

    void DefaultShader::End()
    {
        UnloadShader(_shader);
    }

    Shader DefaultShader::GetShader() const
    {
        return _shader;
    }
}