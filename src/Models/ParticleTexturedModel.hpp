/*
** EPITECH PROJECT, 2021
** indieStudio
** File description:
** ParticleTexturedModel
*/

#pragma once
#ifndef PARTICLETEXTUREDMODEL_HPP_
#define PARTICLETEXTUREDMODEL_HPP_

#include "../include.hpp"
#include "../Models/TexturedModel.hpp"

namespace IS {
    class ParticleTexturedModel : public TexturedModel {
        public:
            ParticleTexturedModel() {};
            ParticleTexturedModel(Mesh mesh, const std::string &texturePath, int numberOfRows);
            ~ParticleTexturedModel();

            int getNumberOfRows() const;

        protected:
        private:
            int _numberOfRows;
    };
}

#endif /* !PARTICLETEXTUREDMODEL_HPP_ */
