/*
** EPITECH PROJECT, 2022
** Hrothgor_Engine
** File description:
** EnvironmentPanel
*/

#include "EnvironmentPanel.hpp"
#include "RenderEngine/Master3DRenderer.hpp"

namespace hr {
    EnvironmentPanel::EnvironmentPanel()
    {
    }

    EnvironmentPanel::~EnvironmentPanel()
    {
    }

    void EnvironmentPanel::ImGuiRender()
    {
        ImGui::Begin("Environment", &_isOpen);

        ImGui::Columns(2);
        ImGui::TextUnformatted("Background Color");
		ImGui::PushItemWidth(-1);
		ImGui::NextColumn();
		ImGui::PushItemWidth(-1);
        ImGui::PushID("Background Color");

        Color col = Master3DRenderer::Get()->GetBackgroundColor();
        Vector4 nCol = ColorNormalize(col);
        float value[4] = {nCol.x, nCol.y, nCol.z, nCol.w};

        if (ImGui::ColorEdit4("", value)) {
            Color newCol = ColorFromNormalized((Vector4){value[0], value[1], value[2], value[3]});
            Master3DRenderer::Get()->SetBackgroundColor(newCol);
        }

        ImGui::PopID();
		ImGui::PopItemWidth();
		ImGui::NextColumn();
        ImGui::Columns();

        ImGui::End();
    }
}
