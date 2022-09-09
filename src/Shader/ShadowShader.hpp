/*
** EPITECH PROJECT, 2022
** Hrothgor_Engine
** File description:
** ShadowShader
*/

#ifndef SHADOWSHADER_HPP_
#define SHADOWSHADER_HPP_

#include "Include.hpp"
#include "DefaultShader.hpp"

namespace hr {
    class ShadowShader : public DefaultShader {
        public:
            ShadowShader();
            ~ShadowShader();

            void UpdateLightSpaceMatrix(Matrix mat);

        protected:
        private:
            int _locationLightSpaceMatrix;
    };
}

#endif /* !SHADOWSHADER_HPP_ */
