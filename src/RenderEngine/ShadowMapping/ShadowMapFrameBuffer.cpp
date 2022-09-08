/*
** EPITECH PROJECT, 2022
** Hrothgor_Engine
** File description:
** ShadowMapFrameBuffer
*/

#include "ShadowMapFrameBuffer.hpp"

namespace hr {
    ShadowMapFrameBuffer::ShadowMapFrameBuffer()
    {
        _fbo = CreateFrameBuffer();
        _shadowMapTexture = CreateDepthBuffer(_textureWidth, _textureHeight);
        UnbindFrameBuffer();
    }

    ShadowMapFrameBuffer::~ShadowMapFrameBuffer()
    {
    }

    void ShadowMapFrameBuffer::BindFrameBuffer()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _fbo);
        glViewport(0, 0, _textureWidth, _textureHeight);
    }

    void ShadowMapFrameBuffer::UnbindFrameBuffer()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, GetScreenWidth(), GetScreenHeight());
    }

    int ShadowMapFrameBuffer::GetFrameBuffer() const
    {
        return _fbo;
    }

    int *ShadowMapFrameBuffer::GetShadowMap()
    {
        return &(_shadowMapTexture);
    }

    int ShadowMapFrameBuffer::CreateFrameBuffer()
    {
        GLuint frameBuffer = 0;

        glGenFramebuffers(1, &frameBuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
        glDrawBuffers(0, GL_NONE);

        return frameBuffer;
    }

    int ShadowMapFrameBuffer::CreateDepthBuffer(int width, int height)
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

    void ShadowMapFrameBuffer::End()
    {
        glDeleteFramebuffers(1, (GLuint *)&_fbo);
        glDeleteTextures(1, (GLuint *)&_shadowMapTexture);
    }
}