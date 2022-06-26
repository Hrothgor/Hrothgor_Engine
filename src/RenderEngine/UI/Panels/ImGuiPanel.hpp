/*
** EPITECH PROJECT, 2022
** Hrothgor_Engine
** File description:
** ImGuiPanel
*/

#ifndef IMGUIPANEL_HPP_
#define IMGUIPANEL_HPP_

#include "Include.hpp"

namespace hr {
    class ImGuiPanel {
        public:
            ImGuiPanel();
            ~ImGuiPanel();

            virtual void Start() = 0;
            virtual void OnEvent() = 0;
            virtual void ImGuiRender() = 0;
            virtual void End() = 0;

            void ActiveEvent(bool val);
            bool IsEvent() const;

            void SetOpen(bool isOpen);
            bool IsOpen();

        protected:
            bool _isOpen = true;
        private:
            bool _isEvent = false;
    };
}

#endif /* !IMGUIPANEL_HPP_ */
