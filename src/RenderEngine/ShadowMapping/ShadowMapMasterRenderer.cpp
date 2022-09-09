/*
** EPITECH PROJECT, 2022
** Hrothgor_Engine
** File description:
** ShadowMapMasterRenderer
*/

#include "ShadowMapMasterRenderer.hpp"

#include "Ecs/GameObject.hpp"

namespace hr {
    ShadowMapMasterRenderer *ShadowMapMasterRenderer::instance = nullptr;

    ShadowMapMasterRenderer::ShadowMapMasterRenderer()
    {
        _lightView = { 0 };
        _lightView.position = { -100, 200, -50 };
        _lightView.target = { 0.0, 0.0, 0.0 };
        _lightView.up = { 0.0, 1.0, 0.0 };
        _lightView.fovy = 150;
        _lightView.projection = CAMERA_ORTHOGRAPHIC;
    }

    ShadowMapMasterRenderer::~ShadowMapMasterRenderer()
    {
    }

    void ShadowMapMasterRenderer::Start()
    {
        _entityRenderer.Start();
    }

    void ShadowMapMasterRenderer::BeginFrame()
    {
        Matrix orthoProjLight = MatrixOrtho(
            -_lightView.fovy / 2, _lightView.fovy / 2,
            -_lightView.fovy / 2, _lightView.fovy / 2,
            RL_CULL_DISTANCE_NEAR, RL_CULL_DISTANCE_FAR);
        Matrix viewLight = MatrixLookAt(
            _lightView.position,
            _lightView.target,
            _lightView.up);
        _lightSpaceMatrix = MatrixMultiply(viewLight, orthoProjLight);

        FrameBuffer.BindFrameBuffer();
        ClearBackground(WHITE);
        BeginMode3D(_lightView);
    }

    void ShadowMapMasterRenderer::Draw()
    {
        BeginFrame();
            _entityRenderer.Draw(_lightSpaceMatrix);
        EndFrame();
    }

    void ShadowMapMasterRenderer::EndFrame()
    {
        EndMode3D();
        FrameBuffer.UnbindFrameBuffer();
    }

    void ShadowMapMasterRenderer::End()
    {
        FrameBuffer.End();
        _entityRenderer.End();
    }

    void ShadowMapMasterRenderer::RegisterObject(GameObject *model)
    {
        _entityRenderer.RegisterObject(model);
    }

    Matrix ShadowMapMasterRenderer::GetLightSpaceMatrix() const
    {
        return _lightSpaceMatrix;
    }
}
