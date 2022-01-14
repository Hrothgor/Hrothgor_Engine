/*
** EPITECH PROJECT, 2021
** 3D
** File description:
** DisplayManager
*/

#pragma once
#ifndef DISPLAYMANAGER_HPP_
#define DISPLAYMANAGER_HPP_

#include "../global.hpp"
#include "../Entities/Camera.hpp"
#include "../Entities/Light.hpp"
#include "../Models/TexturedModel.hpp"
#include "../Particles/ParticleSystem.hpp"
#include "Master3DRenderer.hpp"
#include "Master2DRenderer.hpp"

namespace IS {
    class DisplayManager {
        public:
            DisplayManager();
            ~DisplayManager();

            void run();
            void load();
            void clean();

        protected:
        private:
            Master3DRenderer _3Drenderer;
            Master2DRenderer _2Drenderer;
    };
}

#endif /* !DISPLAYMANAGER_HPP_ */
