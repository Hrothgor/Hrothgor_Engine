/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** ImGuiPanel
*/

#ifndef IMGUIPANEL_HPP_
#define IMGUIPANEL_HPP_

#include "include.hpp"

namespace hr {
    class ImGuiPanel {
        public:
            ImGuiPanel();
            ~ImGuiPanel();

            virtual void ImGuiRender() {}
            void SetOpen(bool isOpen);
            bool IsOpen();

        protected:
            bool _isOpen = true;
        private:
    };
}

#endif /* !IMGUIPANEL_HPP_ */
