/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** ImGuiLayer
*/

#ifndef IMGUILAYER_HPP_
#define IMGUILAYER_HPP_

#include "include.hpp"
#include "Panels/ImGuiPanel.hpp"

namespace hr {
    class ImGuiLayer {
        public:
            ImGuiLayer();
            ~ImGuiLayer();

            void Start();
            void End();

            void BeginFrame();
            void DrawDockSpace();
            void Draw();
            void EndFrame();

            void ImGuiSetStyle();
        protected:
        private:
            std::vector<ImGuiPanel *> _panels;
            // SceneHierarchyPanel _sceneHierarchyPanel;
            // InspectorPanel _inspectorPanel;
            // ViewPortPanel _viewPortPanel;
    };
}

#endif /* !IMGUILAYER_HPP_ */
