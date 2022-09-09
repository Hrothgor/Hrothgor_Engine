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

            void BindFrameBuffer();
            void UnbindFrameBuffer();

            void SetResolution(int resolution);
            int GetResolution() const;

            RenderTexture GetRenderTexture() const;
            Texture GetDepthTexture() const;
            Texture *GetShadowMap();
            
            void End();

        protected:
        private:
            RenderTexture LoadRenderTextureWithDepthTexture(int width, int height);

            RenderTexture _renderTexture;

            int _resolution = 2048;
    };
}


#endif /* !SHADOWMAPFRAMEBUFFER_HPP_ */
