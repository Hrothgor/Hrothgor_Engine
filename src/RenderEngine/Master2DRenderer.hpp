/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** Master2DRenderer
*/

#ifndef MASTER2DRENDERER_HPP_
#define MASTER2DRENDERER_HPP_

#include "../include.hpp"
#include "../Ecs/GameObject.hpp"

class Master2DRenderer {
    public:
        Master2DRenderer();
        ~Master2DRenderer();

        void Start();
        void Draw();
        void End();

        // void Register(GameObject *object);

    protected:
    private:

    protected:
        static Master2DRenderer *instance;
    public:
        Master2DRenderer(Master2DRenderer &other) = delete;
        void operator=(const Master2DRenderer &) = delete;
        static Master2DRenderer *Get() {
            if (instance == nullptr)
                instance = new Master2DRenderer();
            return instance;
        };
};

#endif /* !MASTER2DRENDERER_HPP_ */
