/*
** EPITECH PROJECT, 2022
** Hrothgor_Engine
** File description:
** ShadowMapMasterRenderer
*/

#ifndef SHADOWMAPMASTERRENDERER_HPP_
#define SHADOWMAPMASTERRENDERER_HPP_

#include "Include.hpp"
#include "ShadowMapFrameBuffer.hpp"
#include "ShadowMapEntityRenderer.hpp"

namespace hr {
    class GameObject;

    class ShadowMapMasterRenderer {
        public:
            ShadowMapMasterRenderer();
            ~ShadowMapMasterRenderer();

            void Start();

            void BeginFrame();
            void Draw();
            void EndFrame();

            void End();

            void RegisterObject(GameObject *model);

            void SetLightViewFOV(int fov);
            int GetlightViewFOV() const;

            Matrix GetLightSpaceMatrix() const;

            ShadowMapFrameBuffer FrameBuffer;
        protected:
        private:
            ShadowMapEntityRenderer _entityRenderer;
            Camera _lightView;
            Matrix _lightSpaceMatrix;

        protected:
            static ShadowMapMasterRenderer *instance;
        public:
            ShadowMapMasterRenderer(ShadowMapMasterRenderer &other) = delete;
            void operator=(const ShadowMapMasterRenderer &) = delete;
            static ShadowMapMasterRenderer *Get() {
                if (instance == nullptr)
                    instance = new ShadowMapMasterRenderer();
                return instance;
            };
    };
}

#endif /* !SHADOWMAPMASTERRENDERER_HPP_ */
