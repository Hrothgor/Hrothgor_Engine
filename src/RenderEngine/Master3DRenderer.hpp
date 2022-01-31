/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** Master3DRenderer
*/

#ifndef MASTER3DRENDERER_HPP_
#define MASTER3DRENDERER_HPP_

#include "../include.hpp"
#include "../Ecs/GameObject.hpp"
#include "EntityRenderer.hpp"

class Master3DRenderer {
    public:
        Master3DRenderer();
        ~Master3DRenderer();

        void Start();
        void Draw();
        void End();

        void RegisterObject(GameObject *model);
        void RegisterLight(GameObject *light);
        // void Register(Particle *particles);

    protected:
    private:
        // Camera3D *camera;
        EntityRenderer entityRenderer;

    protected:
        static Master3DRenderer *instance;
    public:
        Master3DRenderer(Master3DRenderer &other) = delete;
        void operator=(const Master3DRenderer &) = delete;
        static Master3DRenderer *Get() {
            if (instance == nullptr)
                instance = new Master3DRenderer();
            return instance;
        };
};

#endif /* !MASTER3DRENDERER_HPP_ */
