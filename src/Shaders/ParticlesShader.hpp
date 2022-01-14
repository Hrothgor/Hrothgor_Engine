/*
** EPITECH PROJECT, 2021
** indieStudio
** File description:
** ParticlesShader
*/

#pragma once
#ifndef PARTICLESSHADER_HPP_
#define PARTICLESSHADER_HPP_

#include "../include.hpp"

namespace IS {
    class ParticlesShader {
        public:
            ParticlesShader();
            ~ParticlesShader();

            void initShader();
            Shader getShader();
            void loadData(Vector2 texoffset1, Vector2 texoffset2, int numberOfRows, float blend);
            void clean();

        protected:
        private:
            Shader _shader;
            int loc_texOffset1;
            int loc_texOffset2;
            int loc_numberOfRows;
            int loc_blend;
    };
}

#endif /* !PARTICLESSHADER_HPP_ */
