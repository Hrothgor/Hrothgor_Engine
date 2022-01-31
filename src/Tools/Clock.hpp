/*
** EPITECH PROJECT, 2022
** indieStudio
** File description:
** Clock
*/

#ifndef CLOCK_HPP_
#define CLOCK_HPP_

#include "../include.hpp"

namespace IS
{
    class Clock
    {
    public:
        Clock();
        ~Clock();

        void reset();
        float getElapsedTime();

    private:
        std::chrono::high_resolution_clock::time_point _clock = std::chrono::high_resolution_clock::now();

    };
}

#endif /* !CLOCK_HPP_ */
