/*
** EPITECH PROJECT, 2022
** Hrothgor_Engine
** File description:
** ProfilerPanel
*/

#ifndef PROFILERPANEL_HPP_
#define PROFILERPANEL_HPP_

#include "Include.hpp"
#include "ImGuiPanel.hpp"
#include "Profiler.hpp"

namespace hr {
    class ProfilerPanel : public ImGuiPanel {
        public:
            ProfilerPanel();
            ~ProfilerPanel();

            virtual void Start() override;
            virtual void OnEvent() override {};
            virtual void ImGuiRender() override;
            virtual void End() override {};
        protected:
        private:
            ImGuiUtils::ProfilersWindow _profilerWindow;
            std::vector<legit::ProfilerTask> _tasks;
    };
}

#endif /* !PROFILERPANEL_HPP_ */
