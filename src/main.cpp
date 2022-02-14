/*
** EPITECH PROJECT, 2022
** indieStudio
** File description:
** main
*/

#include "include.hpp"
#include "Ecs/Engine.hpp"
#include "RenderEngine/AssetsManager.hpp"

int main(void)
{
    srand(time(NULL));

    try {
        hr::Engine::Get()->Start();
        hr::AssetsManager::Get()->Start();
        hr::Engine::Get()->Update();
    }
    catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		hr::Engine::Get()->End();
		return (84);
	}
	hr::Engine::Get()->End();

    return 0;
}