/*
** EPITECH PROJECT, 2022
** Hrothgor_Engine
** File description:
** Master3DRenderer
*/

#ifndef MASTER3DRENDERER_HPP_
#define MASTER3DRENDERER_HPP_

#include "Include.hpp"
#include "EntityRenderer.hpp"
#include "ParticleRenderer.hpp"
#include "GizmosRenderer.hpp"
#include "UI/ImGuiLayer.hpp"

namespace hr {
    class MainCamera3D;
    class GameObject;

    class Master3DRenderer {
        public:
            Master3DRenderer();
            ~Master3DRenderer();

            void Start();
            void End();

            void Clear(Color color);

            void BeginFrame();
            void Draw();
            void EndFrame();

            void RegisterGizmos(GameObject *model);
            void RegisterObject(GameObject *model);
            void RegisterLight(GameObject *light);
            void RegisterParticle(Particle *particles);

            RenderTexture GetRenderTexture() const;
            Texture *GetFrameBufferTexture();

        protected:
        private:
            RenderTexture _renderTexture;

            MainCamera3D *_camera;
            EntityRenderer _entityRenderer;
            ParticleRenderer _particleRenderer;
            GizmosRenderer _gizmosRenderer;

            ImGuiLayer _imGuiLayer;

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
}


#endif /* !MASTER3DRENDERER_HPP_ */
