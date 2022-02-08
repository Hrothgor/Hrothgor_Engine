/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** ViewPortPanel
*/

#include "ViewPortPanel.hpp"
#include "ImGuizmo.h"

#include "../../DisplayManager.hpp"
#include "../../../Ecs/Engine.hpp"
#include "../../../Ecs/GameObject.hpp"

#include "../../../Components/MainCamera3D.hpp"
#include "../../../Components/Transform.hpp"

namespace hr {
    ViewPortPanel::ViewPortPanel()
    {
    }

    ViewPortPanel::~ViewPortPanel()
    {
    }

    void ViewPortPanel::Start()
    {
        _camera = Engine::Get()->GetMainCamera()->GetComponent<MainCamera3D>();
    }

    void ViewPortPanel::ImGuiRender()
    {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2 {0, 0});
        if (ImGui::Begin("Viewport", &_isOpen, ImGuiWindowFlags_NoScrollbar)) {
            ImVec2 size = ImGui::GetContentRegionAvail();
            ImGui::Image((ImTextureID)DisplayManager::Get()->GetFrameBufferTexture(), size, ImVec2 {0, 1}, ImVec2 {1, 0});
            DrawGuizmo();
            ImGui::End();
        }
        ImGui::PopStyleVar();
    }

    void ViewPortPanel::DrawGuizmo()
    {
        GameObject *entity = nullptr;

		if (!(entity = Engine::Get()->GetSelectedEntity()))
            return;

        ImGuizmo::SetOrthographic(false);
        ImGuizmo::AllowAxisFlip(false);
        ImGuizmo::SetDrawlist();
        float windowWidth = (float)ImGui::GetWindowWidth();
        float windowHeight = (float)ImGui::GetWindowHeight();
        ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);

        Matrix cameraProjection = MatrixPerspective(_camera->GetCamera3D().fovy * DEG2RAD, windowWidth / windowHeight, RL_CULL_DISTANCE_NEAR, 5000.0f);
        // Matrix cameraProjection = rlGetMatrixProjection();
        Matrix cameraView = GetCameraMatrix(_camera->GetCamera3D());
        // Matrix cameraView = MatrixLookAt(_camera->GetCamera3D().position, _camera->GetCamera3D().target, _camera->GetCamera3D().up);
        // cameraView = MatrixInvert(cameraView);

        Transform *transform = entity->GetTransform();
        float mat[16];
        ImGuizmo::RecomposeMatrixFromComponents(Vector3ToFloat(transform->GetPositionWorld()),
                                                Vector3ToFloat(transform->GetRotation()),
                                                Vector3ToFloat(transform->GetScale()),
                                                mat);

        ImGuizmo::Manipulate(MatrixToFloat(cameraView), MatrixToFloat(cameraProjection), 
            ImGuizmo::TRANSLATE, ImGuizmo::LOCAL, mat);
        
        if (ImGuizmo::IsUsing()) {
            float translation[3];
            float rotation[3];
            float scale[3];

            ImGuizmo::DecomposeMatrixToComponents(mat, translation, rotation, scale);

            transform->SetPositionFromWorld(translation[0], translation[1], translation[2]);
            transform->SetRotation(rotation[0], rotation[1], rotation[2]);
            transform->SetScale(scale[0], scale[1], scale[2]);
        }
    }

    void ViewPortPanel::End()
    {
    }
}
