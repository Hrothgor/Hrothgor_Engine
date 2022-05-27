/*
** EPITECH PROJECT, 2022
** Hrothgor_Engine
** File description:
** LibraryManager
*/

#ifndef LIBRARYMANAGER_HPP_
#define LIBRARYMANAGER_HPP_

#include "Include.hpp"
#include "../Ecs/Component.hpp"
#include "LDL.hpp"

namespace hr {
    class LibraryManager {
        public:
            LibraryManager();
            ~LibraryManager();

            Component *LoadComponent(const std::string &path);

        protected:
        private:
            std::vector<Component *> _components;
    };
}

#endif /* !LIBRARYMANAGER_HPP_ */
