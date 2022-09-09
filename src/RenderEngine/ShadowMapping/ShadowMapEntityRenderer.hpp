/*
** EPITECH PROJECT, 2022
** Hrothgor_Engine
** File description:
** ShadowMapEntityRenderer
*/

#ifndef SHADOWMAPENTITYRENDERER_HPP_
#define SHADOWMAPENTITYRENDERER_HPP_

#include "Include.hpp"
#include "Shader/ShadowShader.hpp"
#include "ShadowMapFrameBuffer.hpp"

namespace hr {
    class GameObject;

    class ShadowMapEntityRenderer {
        public:
            ShadowMapEntityRenderer();
            ~ShadowMapEntityRenderer();

            void Start();
            void End();

            void BeginFrame(Matrix lightSpaceMatrix);
            void Draw(Matrix lightSpaceMatrix);
            void EndFrame();

            void RegisterObject(GameObject *model);

        protected:
        private:
            std::vector<GameObject *> _objects;
            ShadowShader _shadowShader;
    };
}

#endif /* !SHADOWMAPENTITYRENDERER_HPP_ */
