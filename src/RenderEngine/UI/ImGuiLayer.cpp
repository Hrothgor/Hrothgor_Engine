/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** ImGuiLayer
*/

#include "ImGuiLayer.hpp"
#include "ImGuizmo.h"
#include "Panels/SceneHierarchyPanel.hpp"
#include "Panels/InspectorPanel.hpp"
#include "Panels/ViewPortPanel.hpp"

namespace hr {
    ImGuiLayer::ImGuiLayer()
    {
        _panels.push_back(new SceneHierarchyPanel());
        _panels.push_back(new InspectorPanel());
        _panels.push_back(new ViewPortPanel());
    }

    ImGuiLayer::~ImGuiLayer()
    {
    }

    void ImGuiLayer::Start()
    {
        for (auto &panel : _panels)
            panel->Start();
    }

    void ImGuiLayer::BeginFrame()
    {
        rlImGuiBegin();
        ImGuizmo::BeginFrame();
    }

    void ImGuiLayer::DrawDockSpace()
    {
        ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace", nullptr, window_flags);
        ImGui::PopStyleVar();
        ImGui::PopStyleVar(2);

        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }
        ImGui::End();
    }

    void ImGuiLayer::Draw()
    {
        BeginFrame();
    
        ImGuiSetStyle();

        DrawDockSpace();

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


        for (auto &panel : _panels)
            panel->ImGuiRender();

        EndFrame();
    }

    void ImGuiLayer::EndFrame()
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

    void ImGuiLayer::End()
    {
        for (auto &panel : _panels)
            panel->End();
    }
}
