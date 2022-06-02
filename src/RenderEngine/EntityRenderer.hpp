/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** EntityRenderer
*/

#ifndef ENTITYRENDERER_HPP_
#define ENTITYRENDERER_HPP_

#include "Include.hpp"
#include "Shader/LightShader.hpp"

namespace hr {
    class MainCamera3D;
    class GameObject;

    class EntityRenderer {
        public:
            EntityRenderer();
            ~EntityRenderer();

            void Start();
            void End();

            void BeginFrame();
            void Draw();
            void EndFrame();

            void RegisterLight(GameObject *light);
            void RegisterObject(GameObject *model);

        protected:
        private:
            std::vector<GameObject *> _objects;
            std::vector<GameObject *> _lights;
            LightShader _lightShader;
            MainCamera3D *_camera;
    };
}

#endif /* !ENTITYRENDERER_HPP_ */
