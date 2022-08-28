/*
** EPITECH PROJECT, 2022
** Hrothgor_Engine
** File description:
** DefaultShader
*/

#ifndef DEFAULTSHADER_HPP_
#define DEFAULTSHADER_HPP_

#include "Include.hpp"

namespace hr {
    class DefaultShader {
        public:
            DefaultShader(const std::string &pathVs, const std::string &pathFs);
            ~DefaultShader();

            void Start();
            void End();

            Shader GetShader() const;
        protected:
            Shader _shader;
        private:
    };
}

#endif /* !DEFAULTSHADER_HPP_ */
