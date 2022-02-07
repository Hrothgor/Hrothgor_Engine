/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** ImGuiLayer
*/

#ifndef IMGUILAYER_HPP_
#define IMGUILAYER_HPP_

#include "include.hpp"
#include "Panels/SceneHierarchyPanel.hpp"
#include "Panels/InspectorPanel.hpp"
#include "Panels/ViewPortPanel.hpp"

namespace hr {
    class ImGuiLayer {
        public:
            ImGuiLayer();
            ~ImGuiLayer();

            void Start();
            void DrawDockSpace();
            void Draw();
            void End();

            void ImGuiSetStyle();
        protected:
        private:
            SceneHierarchyPanel _sceneHierarchyPanel;
            InspectorPanel _inspectorPanel;
            ViewPortPanel _viewPortPanel;
    };
}

#endif /* !IMGUILAYER_HPP_ */
