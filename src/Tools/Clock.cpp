/*
** EPITECH PROJECT, 2021
** indieStudio
** File description:
** Clock
*/

#include "Clock.hpp"

IS::Clock::Clock()
{
}

IS::Clock::~Clock()
{
}

void IS::Clock::reset()
{
    _clock = std::chrono::high_resolution_clock::now();
}

float IS::Clock::getElapsedTime()
{
    auto now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::micro> elapsedTime = now - _clock;

    return (elapsedTime.count() / 1000000);
}