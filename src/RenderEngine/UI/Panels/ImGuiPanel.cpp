/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** ImGuiPanel
*/

#include "ImGuiPanel.hpp"

namespace hr {
    ImGuiPanel::ImGuiPanel()
    {
    }

    ImGuiPanel::~ImGuiPanel()
    {
    }

    void ImGuiPanel::SetOpen(bool isOpen)
    {
        _isOpen = isOpen;
    }

    bool ImGuiPanel::IsOpen()
    {
        return _isOpen;
    }
}