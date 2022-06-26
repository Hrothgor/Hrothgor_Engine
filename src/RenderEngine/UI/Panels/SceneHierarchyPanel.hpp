/*
** EPITECH PROJECT, 2022
** Hrothgor_Engine
** File description:
** SceneHierarchyPanel
*/

#ifndef SCENEHIERARCHYPANEL_HPP_
#define SCENEHIERARCHYPANEL_HPP_

#include "Include.hpp"
#include "ImGuiPanel.hpp"

namespace hr {
    class GameObject;
    
    class SceneHierarchyPanel : public ImGuiPanel {
        public:
            SceneHierarchyPanel();
            ~SceneHierarchyPanel();

            virtual void Start() override;
            virtual void OnEvent() override {};
            virtual void ImGuiRender() override;
            virtual void End() override;

            void EntityDraw(GameObject *parent);
        protected:
        private:
    };
}

#endif /* !SCENEHIERARCHYPANEL_HPP_ */
