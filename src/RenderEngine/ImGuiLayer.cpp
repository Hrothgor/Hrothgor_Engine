/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** ImGuiLayer
*/

#include "ImGuiLayer.hpp"
#include "ImGuizmo.h"
#include "DisplayManager.hpp"
#include "../Ecs/Engine.hpp"
#include "../Ecs/GameObject.hpp"

#include "../Components/MainCamera3D.hpp"
#include "../Components/Transform.hpp"

namespace hr {
    ImGuiLayer::ImGuiLayer()
    {
        _camera = Engine::Get()->FindObjectOfType<MainCamera3D>();
    }

    ImGuiLayer::~ImGuiLayer()
    {
    }

    void ImGuiLayer::Start()
    {
        rlImGuiBegin();
        ImGuizmo::BeginFrame();
    }

    void ImGuiLayer::Draw()
    {
        ImGuiSetStyle();

        // ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0);

		// ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
		// if (ImGui::BeginMainMenuBar())
		// {
		// 	if (ImGui::BeginMenu("File"))
		// 	{
		// 		if (ImGui::MenuItem("New Project", "Ctrl+Shift+N"))
		// 			// m_IsProjectManagerOpen = true;

		// 		if (ImGui::MenuItem("Open Project", "Ctrl+Shift+O"))
		// 			// m_IsProjectManagerOpen = true;

		// 		ImGui::Separator();

		// 		if (ImGui::MenuItem("Save Scene", "Ctrl+S"))
		// 		{
		// 			// SceneSerializer sceneSerializer(m_SceneContext->PrimaryScene);
		// 			// sceneSerializer.Serialize(m_EditingProject->GetAssetsDirectoryPath() + static_cast<String>(m_SceneContext->PrimaryScene->GetPath()));
		// 		}

		// 		ImGui::Separator();

		// 		if (ImGui::MenuItem("Quit Editor", "Alt+F4"))
		// 			exit(0);

		// 		ImGui::EndMenu();
		// 	}

		// 	ImGui::EndMainMenuBar();
		// }
		// ImGui::PopStyleVar();

		// ImGui::PopStyleVar();


        _sceneHierarchyPanel.ImGuiRender();
        _inspectorPanel.ImGuiRender();

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2 {0, 0});
        if (ImGui::Begin("Viewport", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove)) {
            ImVec2 size = ImGui::GetContentRegionAvail();
            ImGui::Image((ImTextureID)DisplayManager::Get()->GetFrameBufferTexture(), size, ImVec2 {0, 1}, ImVec2 {1, 0});
            DrawGuizmo();
            ImGui::End();
        }
        ImGui::PopStyleVar();
    }

    void ImGuiLayer::DrawGuizmo()
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

        Matrix cameraProjection = MatrixPerspective(_camera->GetCamera3D().fovy * DEG2RAD, windowWidth / windowHeight, RL_CULL_DISTANCE_NEAR, RL_CULL_DISTANCE_FAR);
        // Matrix cameraProjection = rlGetMatrixProjection();
        Matrix cameraView = (GetCameraMatrix(_camera->GetCamera3D()));
        // Matrix cameraView = MatrixLookAt(_camera->GetCamera3D().position, _camera->GetCamera3D().target, _camera->GetCamera3D().up);
        // cameraView = MatrixInvert(cameraView);

        Transform *transform = entity->GetTransform();
        float mat[16];
        ImGuizmo::RecomposeMatrixFromComponents(Vector3ToFloat(transform->GetPosition()),
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

            transform->SetPosition(translation[0], translation[1], translation[2]);
            transform->SetRotation(rotation[0], rotation[1], rotation[2]);
            transform->SetScale(scale[0], scale[1], scale[2]);
        }
    }

    void ImGuiLayer::End()
    {
        rlImGuiEnd();
    }

    void ImGuiLayer::ImGuiSetStyle()
    {
        ImGui::StyleColorsDark();

        auto& colors = ImGui::GetStyle().Colors;
        colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };

        // Headers
        colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
        colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
        colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
        
        // Buttons
        colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
        colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
        colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

        // Frame BG
        colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
        colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
        colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

        // Tabs
        colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
        colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
        colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
        colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
        colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };

        // Title
        colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
        colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
    }
}
