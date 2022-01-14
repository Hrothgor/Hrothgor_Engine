/*
** EPITECH PROJECT, 2021
** indieStudio
** File description:
** main
*/

#include "include.hpp"
#include "RenderEngine/DisplayManager.hpp"

int main(void)
{
    srand(time(NULL));
    IS::DisplayManager core;
    core.run();
    return 0;
}