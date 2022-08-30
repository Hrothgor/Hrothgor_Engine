/*
** EPITECH PROJECT, 2022
** Hrothgor_Engine
** File description:
** ProfilerPanel
*/

#include "ProfilerPanel.hpp"

namespace hr {
    ProfilerPanel::ProfilerPanel()
    {
    }

    ProfilerPanel::~ProfilerPanel()
    {
    }

    void ProfilerPanel::ImGuiRender()
    {
        ImGui::Begin("Profiler", &_isOpen);

        ImGui::End();
    }
}
