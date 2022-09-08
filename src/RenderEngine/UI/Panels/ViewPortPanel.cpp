/*
** EPITECH PROJECT, 2022
** Hrothgor_Engine
** File description:
** ViewPortPanel
*/

#include "ViewPortPanel.hpp"
#include "Guizmo.hpp"

#include "RenderEngine/Master3DRenderer.hpp"
#include "Ecs/Engine.hpp"
#include "Ecs/GameObject.hpp"
#include "Tools/SaveLoad/LoadSystem.hpp"

#include "Components/MainCamera3D.hpp"
#include "Components/Transform.hpp"

#include "Tools/String.hpp"

namespace hr {
    ViewPortPanel::ViewPortPanel()
    {
        _gizmoType = ImGuizmo::OPERATION::TRANSLATE;
    }

    ViewPortPanel::~ViewPortPanel()
    {
    }

    void ViewPortPanel::Start()
    {
        _camera = Engine::Get()->GetMainCamera()->GetComponent<MainCamera3D>();
    }

    void ViewPortPanel::OnEvent()
    {
        _snap = false;
        bool control = IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL);
        // bool shift = IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT);

        if (control)
            _snap = true;
        if (IsKeyPressed(KEY_ONE) && !IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            _gizmoType = ImGuizmo::OPERATION::TRANSLATE;
        if (IsKeyPressed(KEY_TWO) && !IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            _gizmoType = ImGuizmo::OPERATION::ROTATE;
        if (IsKeyPressed(KEY_THREE) && !IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            _gizmoType = ImGuizmo::OPERATION::SCALE;

        Engine::Get()->GetMainCamera()->GetComponent<MainCamera3D>()->UpdateCameraMovement();
    }

    void ViewPortPanel::ImGuiRender()
    {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2 {0, 0});
        ImGui::Begin("Viewport", &_isOpen, ImGuiWindowFlags_NoScrollbar);

        bool isFocus = ImGui::IsWindowFocused() || ImGui::IsWindowHovered();
        ActiveEvent(isFocus);

        ImVec2 size = ImGui::GetContentRegionAvail();
        if (Engine::Get()->GetProjectName() == "") {
            ImGui::Image((ImTextureID)0, size, ImVec2 {0, 1}, ImVec2 {1, 0}, ImVec4 {0, 0, 0, 1});
        } else {
            ImGui::Image((ImTextureID)Master3DRenderer::Get()->GetFrameBufferTexture(), size, ImVec2 {0, 1}, ImVec2 {1, 0});
        }
        DrawGuizmo();

        if (ImGui::BeginDragDropTarget())
        {
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("SCENE_PAYLOAD"))
            {
                char *path = static_cast<char *>(payload->Data);
                std::string name = String::NameByPath(path);
                name = name.substr(0, name.find("."));
                LoadSystem::LoadProject(name);
            }
            ImGui::EndDragDropTarget();
        }
        ImGui::End();
        ImGui::PopStyleVar();
    }

    void ViewPortPanel::DrawGuizmo()
    {
        GameObject *entity = nullptr;

		if (!(entity = Engine::Get()->GetSelectedEntity()) || _gizmoType == -1)
            return;

        ImGuizmo::SetDrawlist();
        ImGuizmo::AllowAxisFlip(false);
        float windowWidth = (float)ImGui::GetWindowWidth();
        float windowHeight = (float)ImGui::GetWindowHeight();
        ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);

        Matrix cameraProjection = MatrixPerspective(_camera->GetCamera3D().fovy * DEG2RAD, windowWidth / windowHeight, RL_CULL_DISTANCE_NEAR, 5000.0);
        Matrix cameraView = GetCameraMatrix(_camera->GetCamera3D());

        Transform *transform = entity->GetTransform();
        float mat[16];
        ImGuizmo::RecomposeMatrixFromComponents(Vector3ToFloat(transform->GetPositionWorld()),
                                                Vector3ToFloat(transform->GetRotation()),
                                                Vector3ToFloat(transform->GetScaleWorld()),
                                                mat);

        // Snapping
        float snapValue = 0.5;
        if (_gizmoType == ImGuizmo::OPERATION::ROTATE)
            snapValue = 45;
        
        float snapValues[3] = {snapValue, snapValue, snapValue};

        ImGuizmo::Manipulate(MatrixToFloat(cameraView), MatrixToFloat(cameraProjection), 
            (ImGuizmo::OPERATION)_gizmoType, ImGuizmo::WORLD, mat,
            MatrixToFloat(MatrixIdentity()), _snap ? snapValues : nullptr);
        
        if (ImGuizmo::IsUsing()) {
            float translation[3];
            float rotation[3];
            float scale[3];

            ImGuizmo::DecomposeMatrixToComponents(mat, translation, rotation, scale);

            transform->SetPositionFromWorld(translation[0], translation[1], translation[2]);
            transform->SetRotation(rotation[0], rotation[1], rotation[2]);
            transform->SetScaleFromWorld(scale[0], scale[1], scale[2]);
        }
    }

    void ViewPortPanel::End()
    {
    }
}
