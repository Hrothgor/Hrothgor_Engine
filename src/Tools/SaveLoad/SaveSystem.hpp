/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** SaveSystem
*/

#ifndef SAVESYSTEM_HPP_
#define SAVESYSTEM_HPP_

#include "Include.hpp"
#include "Json.hpp"

namespace hr {
    class GameObject;

    class SaveSystem {
        public:
            static void SaveProject(const std::string &name);
            static json SaveEntity(GameObject *entity);
        protected:
        private:
    };
}

#endif /* !SAVESYSTEM_HPP_ */
