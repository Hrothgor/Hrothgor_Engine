/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** GizmosRenderer
*/

#ifndef GIZMOSRENDERER_HPP_
#define GIZMOSRENDERER_HPP_

#include "Include.hpp"

namespace hr {
    class GameObject;

    class GizmosRenderer {
        public:
            GizmosRenderer();
            ~GizmosRenderer();

            void Start();
            void End();

            void BeginFrame();
            void Draw();
            void EndFrame();

            void RegisterObject(GameObject *object);
        protected:
        private:
            std::vector<GameObject *> _objects;
    };
}

#endif /* !GIZMOSRENDERER_HPP_ */
