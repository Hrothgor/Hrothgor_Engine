/*
** EPITECH PROJECT, 2022
** Hrothgor_Engine
** File description:
** LibraryManager
*/

#include "LibraryManager.hpp"

namespace hr {
    LibraryManager::LibraryManager()
    {
    }

    LibraryManager::~LibraryManager()
    {
    }

    Component *LibraryManager::LoadComponent(const std::string &name)
    {
        void *handle = LDL::open(name.c_str());
        Component *(*entryPoint)(void) = NULL;

        if (!handle)
            std::cout << "Unable to load library " + name + " : " + LDL::error() << std::endl;

        *(void **)(&entryPoint) = LDL::sym(handle, "entryPoint");
        if (entryPoint == NULL)
            std::cout << "Unable to load library " + name + " : Invalid library" << std::endl;

        Component *component = entryPoint();
        LDL::close(handle);
        return (component);
    }
}

