/*
** EPITECH PROJECT, 2022
** Hrothgor_Engine
** File description:
** EnvironmentPanel
*/

#ifndef ENVIRONMENTPANEL_HPP_
#define ENVIRONMENTPANEL_HPP_

#include "Include.hpp"
#include "ImGuiPanel.hpp"

namespace hr {
    class EnvironmentPanel : public ImGuiPanel {
        public:
            EnvironmentPanel();
            ~EnvironmentPanel();

            virtual void Start() override {};
            virtual void OnEvent() override {};
            virtual void ImGuiRender() override;
            virtual void End() override {};

            void StartField(const std::string &label);
            void EndField();
        protected:
        private:
    };
}

#endif /* !ENVIRONMENTPANEL_HPP_ */
