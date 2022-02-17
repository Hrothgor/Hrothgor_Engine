/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** SmoothPositionSolver
*/

#ifndef SMOOTHPOSITIONSOLVER_HPP_
#define SMOOTHPOSITIONSOLVER_HPP_

#include "include.hpp"
#include "Solver.hpp"

namespace hr {
    class SmoothPositionSolver : public Solver {
        public:
            SmoothPositionSolver();
            ~SmoothPositionSolver();

            virtual void Solve(std::vector<Collision> &collisions) override;

        protected:
        private:
    };
}

#endif /* !SMOOTHPOSITIONSOLVER_HPP_ */
