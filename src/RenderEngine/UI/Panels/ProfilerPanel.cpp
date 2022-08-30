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

    void ProfilerPanel::Start()
    {
        _profilerWindow = ImGuiUtils::ProfilersWindow();
        _profilerWindow.frameWidth = 4;
    }

    void ProfilerPanel::ImGuiRender()
    {
        _tasks.clear();

        float start = 0;
        float end = 0;

        end += (float)(rand() % 2 + 1) / 1000;
        _tasks.push_back({
            start,
            end,
            "Test 1",
            legit::Colors::peterRiver
        });
        start = end;
        end += (float)(rand() % 2 + 2) / 1000;
        _tasks.push_back({
            start,
            end,
            "Test 2",
            legit::Colors::emerald
        });
        start = end;
        end += (float)(rand() % 4 + 3) / 1000;
        _tasks.push_back({
            start,
            end,
            "Test 3",
            legit::Colors::orange
        });

        _profilerWindow.cpuGraph.LoadFrameData(&_tasks[0], _tasks.size());

        _profilerWindow.Render();
    }
}
