/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** CreatePrimitive
*/

#ifndef CREATEPRIMITIVE_HPP_
#define CREATEPRIMITIVE_HPP_

#include "Include.hpp"

namespace hr {
    class GameObject;
    namespace CreatePrimitive {
        GameObject *CreateEmpty(GameObject *parent = nullptr);
        GameObject *CreateSphere(GameObject *parent = nullptr);
        GameObject *CreateBox(GameObject *parent = nullptr);
        GameObject *CreateMesh(GameObject *parent = nullptr);
        GameObject *CreateLight(GameObject *parent = nullptr);
    }
}

#endif /* !CREATEPRIMITIVE_HPP_ */
