/*
** EPITECH PROJECT, 2022
** indieStudio
** File description:
** main
*/

#include "include.hpp"
#include "Ecs/Engine.hpp"

int main(void)
{
    srand(time(NULL));

    try {
        Engine::Get()->Start();
        Engine::Get()->Update();
    }
    catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		Engine::Get()->End();
		return (84);
	}
	Engine::Get()->End();

    return 0;
}