/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** DefaultShader
*/

#ifndef DEFAULTSHADER_HPP_
#define DEFAULTSHADER_HPP_

#include "../include.hpp"

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
