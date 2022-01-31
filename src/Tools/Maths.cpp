/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** Maths
*/

#include "Maths.hpp"

IS::Maths::Maths()
{
}

IS::Maths::~Maths()
{
}

float IS::Maths::randFloat()
{
    float scale = rand() / (float) RAND_MAX;
    return (scale);
}