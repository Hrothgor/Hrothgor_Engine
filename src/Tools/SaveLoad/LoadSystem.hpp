/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** LoadSystem
*/

#ifndef LOADSYSTEM_HPP_
#define LOADSYSTEM_HPP_

#include "Include.hpp"
#include "Json.hpp"

namespace hr {
    class GameObject;

    class LoadSystem {
        public:
            static void LoadProject(const std::string &name);
            static GameObject *LoadEntity(const nlohmann::json &json);
        protected:
        private:
    };
}

#endif /* !LOADSYSTEM_HPP_ */
