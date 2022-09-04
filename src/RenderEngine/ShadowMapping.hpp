/*
** EPITECH PROJECT, 2022
** Hrothgor_Engine
** File description:
** ShadowMapping
*/

#ifndef SHADOWMAPPING_HPP_
#define SHADOWMAPPING_HPP_

#include "Include.hpp"

namespace hr {
    class ShadowMapping {
        public:
            ShadowMapping();
            ~ShadowMapping();

            void End();

            void BindFrameBuffer();
            
        protected:
        private:
            int CreateFrameBuffer();
            int CreateDepthBuffer(int width, int height);

            RenderTexture _depthTexture;

            int _fbo;
            int _shadowMapTexture;

            int _textureWidth = 2048;
            int _textureHeight = 2048;

        protected:
            static ShadowMapping *instance;
        public:
            ShadowMapping(ShadowMapping &other) = delete;
            void operator=(const ShadowMapping &) = delete;
            static ShadowMapping *Get() {
                if (instance == nullptr)
                    instance = new ShadowMapping();
                return instance;
            };
    };
}


#endif /* !SHADOWMAPPING_HPP_ */
