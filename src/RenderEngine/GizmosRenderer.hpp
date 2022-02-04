/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** GizmosRenderer
*/

#ifndef GIZMOSRENDERER_HPP_
#define GIZMOSRENDERER_HPP_

#include "include.hpp"

namespace hr {
    class GameObject;

    class GizmosRenderer {
        public:
            GizmosRenderer();
            ~GizmosRenderer();

            void Start();
            void Draw();
            void End();

            void RegisterObject(GameObject *object);
        protected:
        private:
            std::vector<GameObject *> _objects;
    };
}

#endif /* !GIZMOSRENDERER_HPP_ */
