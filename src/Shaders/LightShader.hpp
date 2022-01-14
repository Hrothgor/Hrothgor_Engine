/*
** EPITECH PROJECT, 2021
** indieStudio
** File description:
** LightShader
*/

#pragma once
#ifndef LIGHTSHADER_HPP_
#define LIGHTSHADER_HPP_

#include "../include.hpp"

namespace IS {
    class LightShader {
        public:
            LightShader();
            ~LightShader();

            void initShader();
            Shader getShader();
            void clean();

        protected:
        private:
            Shader _shader;
    };
}

#endif /* !LIGHTSHADER_HPP_ */
