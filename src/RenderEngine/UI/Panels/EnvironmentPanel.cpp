/*
** EPITECH PROJECT, 2022
** Hrothgor_Engine
** File description:
** EnvironmentPanel
*/

#include "EnvironmentPanel.hpp"
#include "RenderEngine/Master3DRenderer.hpp"
#include "RenderEngine/ShadowMapping/ShadowMapMasterRenderer.hpp"

namespace hr {
    EnvironmentPanel::EnvironmentPanel()
    {
    }

    EnvironmentPanel::~EnvironmentPanel()
    {
    }

    void EnvironmentPanel::StartField(const std::string &label)
    {
        ImGui::Columns(2);
        ImGui::TextUnformatted(label.c_str());
		ImGui::PushItemWidth(-1);
		ImGui::NextColumn();
		ImGui::PushItemWidth(-1);
        ImGui::PushID(label.c_str());
    }

    void EnvironmentPanel::EndField()
    {
        ImGui::PopID();
		ImGui::PopItemWidth();
		ImGui::NextColumn();
        ImGui::Columns();
    }

    void EnvironmentPanel::ImGuiRender()
    {
        ImGui::Begin("Environment", &_isOpen);

        // Background Color
        StartField("Background Color");

        Color col = Master3DRenderer::Get()->GetBackgroundColor();
        Vector4 nCol = ColorNormalize(col);
        float bCol[4] = {nCol.x, nCol.y, nCol.z, nCol.w};

        if (ImGui::ColorEdit4("", bCol)) {
            Color newCol = ColorFromNormalized((Vector4){bCol[0], bCol[1], bCol[2], bCol[3]});
            Master3DRenderer::Get()->SetBackgroundColor(newCol);
        }

        EndField();
        //

        // Shadow Map
        ImGui::SetWindowFontScale(1.5);
        ImGui::TextColored(ImVec4(9.0 / 255, 94.0 / 255, 149.0 / 255, 1), "Shadow Map");
        ImGui::SetWindowFontScale(1);

        ImGui::BeginDisabled(); // Disabled for the moment
            StartField("Map resolution");

            int resolution = ShadowMapMasterRenderer::Get()->FrameBuffer.GetResolution();
            int minRes = 1;
            if (ImGui::DragScalarN("", ImGuiDataType_S32, &resolution, 1, 1, &minRes))
                ShadowMapMasterRenderer::Get()->FrameBuffer.SetResolution(resolution);

            EndField();
        ImGui::EndDisabled();
        //

        ImGui::End();
    }
}
