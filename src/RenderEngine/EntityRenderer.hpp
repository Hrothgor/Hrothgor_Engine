/*
** EPITECH PROJECT, 2021
** indieStudio
** File description:
** EntityRenderer
*/

#pragma once
#ifndef ENTITYRENDERER_HPP_
#define ENTITYRENDERER_HPP_

#include "../include.hpp"
#include "../Entities/Camera.hpp"
#include "../Entities/Entity.hpp"
#include "../Entities/Light.hpp"
#include "../Shaders/LightShader.hpp"
#include "rlights.h"

namespace IS {
    class EntityRenderer {
        public:
            EntityRenderer();
            ~EntityRenderer();

            void prepare(int scene, Camera *camera);
            void render(int scene, IS::Camera *camera);
            void prepareEntity(Entity *entity);
            void clear(int scene);

            void addLight(int scene, const LightValue &light);
            void addEntity(int scene, Entity *entity);

        protected:
        private:
            LightShader _lightShader;

            std::vector<Light> _lights;
            std::map<int, std::vector<Entity *>> _entities;
    };
}

#endif /* !ENTITYRENDERER_HPP_ */
