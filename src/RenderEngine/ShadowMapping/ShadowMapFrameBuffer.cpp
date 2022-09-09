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
        _renderTexture = LoadRenderTextureWithDepthTexture(_resolution, _resolution);
    }

    ShadowMapFrameBuffer::~ShadowMapFrameBuffer()
    {
    }

    unsigned int ShadowMapFrameBuffer::LoadTextureDepth(int width, int height)
    {
        unsigned int id = 0;

        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

        glBindTexture(GL_TEXTURE_2D, 0);

        return id;
    }

    RenderTexture2D ShadowMapFrameBuffer::LoadRenderTextureWithDepthTexture(int width, int height)
    {
        RenderTexture2D target = {0};

        target.id = rlLoadFramebuffer(width, height);   // Load an empty framebuffer

        if (target.id > 0)
        {
            rlEnableFramebuffer(target.id);

            // Create color texture (default to RGBA)
            target.texture.id = rlLoadTexture(NULL, width, height, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8, 1);
            target.texture.width = width;
            target.texture.height = height;
            target.texture.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;
            target.texture.mipmaps = 1;

            // Create depth texture
            target.depth.id = LoadTextureDepth(width, height);
            target.depth.width = width;
            target.depth.height = height;
            target.depth.format = 19;       //DEPTH_COMPONENT_24BIT?
            target.depth.mipmaps = 1;

            // Attach color texture and depth texture to FBO
            rlFramebufferAttach(target.id, target.texture.id, RL_ATTACHMENT_COLOR_CHANNEL0, RL_ATTACHMENT_TEXTURE2D, 0);
            rlFramebufferAttach(target.id, target.depth.id, RL_ATTACHMENT_DEPTH, RL_ATTACHMENT_TEXTURE2D, 0);

            // Check if fbo is complete with attachments (valid)
            if (rlFramebufferComplete(target.id)) TRACELOG(LOG_INFO, "FBO: [ID %i] Framebuffer object created successfully", target.id);

            rlDisableFramebuffer();
        } 
        else TRACELOG(LOG_WARNING, "FBO: Framebuffer object can not be created");

        return target;
    }

    void ShadowMapFrameBuffer::BindFrameBuffer()
    {
        BeginTextureMode(_renderTexture);
    }

    void ShadowMapFrameBuffer::UnbindFrameBuffer()
    {
        EndTextureMode();
    }

    void ShadowMapFrameBuffer::SetResolution(int resolution)
    {
        _resolution = resolution;
        UnloadRenderTexture(_renderTexture);
        _renderTexture = LoadRenderTextureWithDepthTexture(_resolution, _resolution);
    }

    int ShadowMapFrameBuffer::GetResolution() const
    {
        return _resolution;
    }

    RenderTexture ShadowMapFrameBuffer::GetRenderTexture() const
    {
        return _renderTexture;
    }

    Texture ShadowMapFrameBuffer::GetDepthTexture() const
    {
        return _renderTexture.depth;
    }

    Texture *ShadowMapFrameBuffer::GetShadowMap()
    {
        return &(_renderTexture.texture);
    }

    void ShadowMapFrameBuffer::End()
    {
        UnloadRenderTexture(_renderTexture);
    }
}