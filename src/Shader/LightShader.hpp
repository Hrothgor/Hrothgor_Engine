/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** LightShader
*/

#ifndef LIGHTSHADER_HPP_
#define LIGHTSHADER_HPP_

#include "../include.hpp"
#include "DefaultShader.hpp"

namespace hr {
    class LightShader : public DefaultShader {
        public:
            LightShader();
            ~LightShader();

            void UpdateCameraLoc(Camera3D camera);

        protected:
        private:
    };
}

#endif /* !LIGHTSHADER_HPP_ */
