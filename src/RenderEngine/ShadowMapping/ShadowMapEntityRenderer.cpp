/*
** EPITECH PROJECT, 2022
** Hrothgor_Engine
** File description:
** ShadowMapEntityRenderer
*/

#include "ShadowMapEntityRenderer.hpp"
#include "Ecs/GameObject.hpp"

#include "Components/Transform.hpp"
#include "Components/MeshRenderer.hpp"

namespace hr {
    ShadowMapEntityRenderer::ShadowMapEntityRenderer()
    {
    }

    ShadowMapEntityRenderer::~ShadowMapEntityRenderer()
    {
    }

    void ShadowMapEntityRenderer::Start()
    {

    }

    void ShadowMapEntityRenderer::BeginFrame(Matrix lightSpaceMatrix)
    {
        _shadowShader.UpdateLightSpaceMatrix(lightSpaceMatrix);
    }

    void ShadowMapEntityRenderer::Draw(Matrix lightSpaceMatrix)
    {
        BeginFrame(lightSpaceMatrix);
        for (GameObject *object : _objects) {
            Transform *transform = object->GetTransform();
            MeshRenderer *meshRenderer = object->GetComponent<MeshRenderer>();

            Model model = meshRenderer->GetModel();
            Texture texture = meshRenderer->GetTexture();
            AxisAngle axisAngle = transform->GetRotationAxisAngle();
            
            for (int i = 0; i < model.materialCount; i++)
                model.materials[i].shader = _shadowShader.GetShader();
            if (model.materialCount > 0 && texture.id != 0)
                SetMaterialTexture(&(model.materials[0]), MATERIAL_MAP_DIFFUSE, texture);
            else if (model.materialCount > 0)
                SetMaterialTexture(&(model.materials[0]), MATERIAL_MAP_DIFFUSE, (Texture2D){ rlGetTextureIdDefault(), 1, 1, 1, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8 });

            if (meshRenderer->GetHasTransparency())
                rlDisableBackfaceCulling();

            DrawModelEx(model, transform->GetPositionWorld(), axisAngle.axis, axisAngle.angle, transform->GetScaleWorld(), meshRenderer->GetColor());
        
            if (meshRenderer->GetHasTransparency())
                rlEnableBackfaceCulling();
        }
        EndFrame();
    }

    void ShadowMapEntityRenderer::EndFrame()
    {
        _objects.clear();
        rlEnableBackfaceCulling();
    }

    void ShadowMapEntityRenderer::End()
    {
        _shadowShader.End();
    }

    void ShadowMapEntityRenderer::RegisterObject(GameObject *object)
    {
        _objects.push_back(object);
    }
}
