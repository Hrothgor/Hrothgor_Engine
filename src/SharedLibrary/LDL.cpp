/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** LDL
*/

#include "LDL.hpp"

namespace hr {
    void *LDL::open(const char *path)
    {
        return (dlmopen(LM_ID_NEWLM, path, RTLD_NOW));
    }

    char *LDL::error()
    {
        return (dlerror());
    }

    void *LDL::sym(void *handle, const char *symbol)
    {
        return (dlsym(handle, symbol));
    }

    int LDL::close(void *handle)
    {
        return (dlclose(handle));
    }
}