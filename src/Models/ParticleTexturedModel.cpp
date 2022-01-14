/*
** EPITECH PROJECT, 2021
** indieStudio
** File description:
** ParticleTexturedModel
*/

#include "ParticleTexturedModel.hpp"

IS::ParticleTexturedModel::ParticleTexturedModel(Mesh mesh, const std::string &texturePath, int numberOfRows)
    : TexturedModel(mesh, texturePath)
{
    _numberOfRows = numberOfRows;
}

IS::ParticleTexturedModel::~ParticleTexturedModel()
{
}

int IS::ParticleTexturedModel::getNumberOfRows() const
{
    return (_numberOfRows);
}