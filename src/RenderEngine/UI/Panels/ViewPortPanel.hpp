/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** ViewPortPanel
*/

#ifndef VIEWPORTPANEL_HPP_
#define VIEWPORTPANEL_HPP_

#include "include.hpp"
#include "ImGuiPanel.hpp"

namespace hr {
    class MainCamera3D;

    class ViewPortPanel : public ImGuiPanel {
        public:
            ViewPortPanel();
            ~ViewPortPanel();
            
            virtual void Start() override;
            virtual void OnEvent() override;
            virtual void ImGuiRender() override;
            virtual void End() override;

            void DrawGuizmo();
        protected:
        private:
            MainCamera3D *_camera;
            int _gizmoType;
            bool _snap;
    };
}

#endif /* !VIEWPORTPANEL_HPP_ */
