/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** ImGuiLayer
*/

#ifndef IMGUILAYER_HPP_
#define IMGUILAYER_HPP_

#include "include.hpp"
#include "UI/Panels/SceneHierarchyPanel.hpp"
#include "UI/Panels/InspectorPanel.hpp"

namespace hr {
    class MainCamera3D;

    class ImGuiLayer {
        public:
            ImGuiLayer();
            ~ImGuiLayer();

            void Start();
            void Draw();
            void End();

            void DrawGuizmo();

            void ImGuiSetStyle();
        protected:
        private:
            MainCamera3D *_camera;
            SceneHierarchyPanel _sceneHierarchyPanel;
            InspectorPanel _inspectorPanel;
    };
}

#endif /* !IMGUILAYER_HPP_ */
