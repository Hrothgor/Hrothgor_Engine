/*
** EPITECH PROJECT, 2022
** Hrothgor_Engine
** File description:
** ShadowMapPanel
*/

#ifndef SHADOWMAPPANEL_HPP_
#define SHADOWMAPPANEL_HPP_

#include "Include.hpp"
#include "ImGuiPanel.hpp"

namespace hr {
    class ShadowMapPanel : public ImGuiPanel {
        public:
            ShadowMapPanel();
            ~ShadowMapPanel();

            virtual void Start() override {};
            virtual void OnEvent() override {};
            virtual void ImGuiRender() override;
            virtual void End() override {};
        protected:
        private:
    };
}

#endif /* !SHADOWMAPPANEL_HPP_ */
