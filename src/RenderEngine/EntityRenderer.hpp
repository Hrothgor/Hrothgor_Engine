/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** EntityRenderer
*/

#ifndef ENTITYRENDERER_HPP_
#define ENTITYRENDERER_HPP_

#include "../include.hpp"
#include "rlights.h"

class GameObject;

class EntityRenderer {
    public:
        EntityRenderer();
        ~EntityRenderer();

        void Start();
        void Draw();
        void End();

        void RegisterLight(GameObject *light);
        void RegisterObject(GameObject *model);

    protected:
    private:
        std::vector<GameObject *> _objects;
        std::vector<GameObject *> _lights;
};

#endif /* !ENTITYRENDERER_HPP_ */
