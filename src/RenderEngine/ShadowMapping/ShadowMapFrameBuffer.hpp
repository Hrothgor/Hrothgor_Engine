/*
** EPITECH PROJECT, 2022
** Hrothgor_Engine
** File description:
** ShadowMapFrameBuffer
*/

#ifndef SHADOWMAPFRAMEBUFFER_HPP_
#define SHADOWMAPFRAMEBUFFER_HPP_

#include "Include.hpp"

namespace hr {
    class ShadowMapFrameBuffer {
        public:
            ShadowMapFrameBuffer();
            ~ShadowMapFrameBuffer();

            void End();

            void BindFrameBuffer();
            void UnbindFrameBuffer();

            int GetFrameBuffer() const;
            int *GetShadowMap();
            
        protected:
        private:
            int CreateFrameBuffer();
            int CreateDepthBuffer(int width, int height);

            RenderTexture _depthTexture;

            int _fbo;
            int _shadowMapTexture;

            int _textureWidth = 2048;
            int _textureHeight = 2048;
    };
}


#endif /* !SHADOWMAPFRAMEBUFFER_HPP_ */
