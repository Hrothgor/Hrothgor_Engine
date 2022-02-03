/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** InspectorPanel
*/

#ifndef INSPECTORPANEL_HPP_
#define INSPECTORPANEL_HPP_

#include "../../../include.hpp"
#include "ImGuiPanel.hpp"

namespace hr {
    class InspectorPanel : public ImGuiPanel {
        public:
            InspectorPanel();
            ~InspectorPanel();
                
            virtual void ImGuiRender() override;
        protected:
        private:
    };
}

#endif /* !INSPECTORPANEL_HPP_ */
