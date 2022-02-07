/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** LoadSystem
*/

#ifndef LOADSYSTEM_HPP_
#define LOADSYSTEM_HPP_

#include "include.hpp"
#include "json.hpp"

namespace hr {
    class GameObject;

    class LoadSystem {
        public:
            static void LoadProject(const std::string &fileName);
            static GameObject *LoadEntity(const nlohmann::json &json);
            static void NewProject();
        protected:
        private:
    };
}

#endif /* !LOADSYSTEM_HPP_ */
