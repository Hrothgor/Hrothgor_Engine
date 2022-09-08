/*
** EPITECH PROJECT, 2022
** Hrothgor_Engine
** File description:
** ShadowMapEntityRenderer
*/

#ifndef SHADOWMAPENTITYRENDERER_HPP_
#define SHADOWMAPENTITYRENDERER_HPP_

#include "Include.hpp"
#include "ShadowMapFrameBuffer.hpp"
#include "Shader/ShadowShader.hpp"

namespace hr {
    class GameObject;

    class ShadowMapEntityRenderer {
        public:
            ShadowMapEntityRenderer();
            ~ShadowMapEntityRenderer();

            void Start();
            void End();

            void BeginFrame();
            void Draw();
            void EndFrame();

            void RegisterObject(GameObject *model);

            int *GetShadowMapTexture();

        protected:
        private:
            std::vector<GameObject *> _objects;
            ShadowShader _shadowShader;
            ShadowMapFrameBuffer _shadowFBO;
    };
}

#endif /* !SHADOWMAPENTITYRENDERER_HPP_ */
