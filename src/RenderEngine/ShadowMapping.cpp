/*
** EPITECH PROJECT, 2022
** Hrothgor_Engine
** File description:
** ShadowMapping
*/

#include "ShadowMapping.hpp"

namespace hr {
    ShadowMapping *ShadowMapping::instance = nullptr;

    ShadowMapping::ShadowMapping()
    {
        _fbo = CreateFrameBuffer();
        _shadowMapTexture = CreateDepthBuffer(_textureWidth, _textureHeight);
    }

    ShadowMapping::~ShadowMapping()
    {
    }

    void ShadowMapping::BindFrameBuffer()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _fbo);
        glViewport(0, 0, _textureWidth, _textureHeight);
    }

    int ShadowMapping::CreateFrameBuffer()
    {
        GLuint frameBuffer = 0;

        glGenFramebuffers(1, &frameBuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
        glDrawBuffers(0, GL_NONE);

        return frameBuffer;
    }

    int ShadowMapping::CreateDepthBuffer(int width, int height)
    {
        GLuint depthTexture = 0;

        glGenTextures(1, &depthTexture);
        glBindTexture(GL_TEXTURE_2D, depthTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTexture, 0, 0);

        return depthTexture;
    }

    void ShadowMapping::End()
    {
        glDeleteFramebuffers(1, (GLuint *)&_fbo);
        glDeleteTextures(1, (GLuint *)&_shadowMapTexture);
    }
}
