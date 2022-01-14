/*
** EPITECH PROJECT, 2021
** indieStudio
** File description:
** GenMesh
*/

#pragma once
#ifndef GENMESH_HPP_
#define GENMESH_HPP_

#include "../include.hpp"

namespace IS {
    class GenMesh {
        public:
            GenMesh();
            ~GenMesh();

            static Mesh GenMeshSquare(float size);

        protected:
        private:
    };
}

#endif /* !GENMESH_HPP_ */
