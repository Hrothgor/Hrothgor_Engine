/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** SceneHierarchyPanel
*/

#ifndef SCENEHIERARCHYPANEL_HPP_
#define SCENEHIERARCHYPANEL_HPP_

#include "../../../include.hpp"
#include "ImGuiPanel.hpp"

namespace hr {
    class GameObject;
    
    class SceneHierarchyPanel : public ImGuiPanel {
        public:
            SceneHierarchyPanel();
            ~SceneHierarchyPanel();

            virtual void ImGuiRender() override;

            void EntityDraw(GameObject *parent);
        protected:
        private:
    };
}

#endif /* !SCENEHIERARCHYPANEL_HPP_ */
