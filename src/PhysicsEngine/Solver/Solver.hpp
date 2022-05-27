/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** Solver
*/

#ifndef SOLVER_HPP_
#define SOLVER_HPP_

#include "Include.hpp"
#include "../../Components/Collider/Collider.hpp"

namespace hr {
    class Solver {
        public:
            virtual void Solve(std::vector<Collision> &collisions) = 0;
    };
}

#endif /* !SOLVER_HPP_ */
