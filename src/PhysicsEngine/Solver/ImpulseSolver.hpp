/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** ImpulseSolver
*/

#ifndef IMPULSESOLVER_HPP_
#define IMPULSESOLVER_HPP_

#include "Include.hpp"
#include "Solver.hpp"

namespace hr {
    class ImpulseSolver : public Solver {
        public:
            ImpulseSolver();
            ~ImpulseSolver();

            virtual void Solve(std::vector<Collision> &collisions) override;

        protected:
        private:
    };
}

#endif /* !IMPULSESOLVER_HPP_ */
