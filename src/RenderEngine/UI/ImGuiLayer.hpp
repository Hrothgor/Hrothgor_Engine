/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** ImGuiLayer
*/

#ifndef IMGUILAYER_HPP_
#define IMGUILAYER_HPP_

#include "Include.hpp"
#include "Panels/ImGuiPanel.hpp"

namespace hr {
    class ImGuiLayer {
        public:
            ImGuiLayer();
            ~ImGuiLayer();

            void Start();
            void End();

            void BeginFrame();
            void ImGuiSetStyle();
            void Event();
            void EndFrame();

            void DrawDockSpace();
            void DrawToolBarUi();
            void Draw();

        protected:
        private:
            std::vector<ImGuiPanel *> _panels;
            float menuBarHeight;
            float toolbarSize = 50;
    };
}

#endif /* !IMGUILAYER_HPP_ */
