/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** UIElement
*/

#include "UIElement.hpp"

namespace hr {
    // UIElement::UIElement()
    // {
    // }

    // UIElement::~UIElement()
    // {
    // }

    void UIElement::CheckBox(const std::string &label, bool (*getter)(void), void (*setter)(bool))
    {
        bool value = getter();
        
        ImGui::Columns(2);
        ImGui::TextUnformatted(label.c_str());
		ImGui::NextColumn();
    
        ImGui::PushID(label.c_str());
        if (ImGui::Checkbox("", &value))
            setter(value);
        ImGui::PopID();

		ImGui::NextColumn();
        ImGui::Columns();
    }

    void UIElement::FloatField(const std::string &label, float (*getter)(void), void (*setter)(float), float speed, float min, float max, const char* format)
    {
        float value = getter();

        ImGui::Columns(2);
        ImGui::TextUnformatted(label.c_str());
		ImGui::NextColumn();
		ImGui::PushItemWidth(-1);
		ImGui::PushID(label.c_str());

		if (ImGui::DragScalarN("", ImGuiDataType_Float, &value, 1, speed, &min, &max, format))
            setter(value);

		ImGui::PopID();
		ImGui::PopItemWidth();
		ImGui::NextColumn();
        ImGui::Columns();
    }

    void UIElement::Vector2Field(const std::string &label, Vector2 (*getter)(void), void (*setter)(Vector2), float speed, float min, float max, const char* format)
    {
        Vector2 vec = getter();
        float value[2] = {vec.x, vec.y};

        ImGui::Columns(2);
        ImGui::TextUnformatted(label.c_str());
		ImGui::NextColumn();
		ImGui::PushItemWidth(-1);
		ImGui::PushID(label.c_str());

		if (ImGui::DragScalarN("", ImGuiDataType_Float, value, 2, speed, &min, &max, format))
            setter((Vector2){value[0], value[1]});

		ImGui::PopID();
		ImGui::PopItemWidth();
		ImGui::NextColumn();
        ImGui::Columns();
    }

    void UIElement::Vector3Field(const std::string &label, std::function<Vector3()> getter, std::function<void(Vector3)> setter, float speed, float min, float max, const char* format)
    {
        Vector3 vec = getter();
        float value[3] = {vec.x, vec.y, vec.z};

        ImGui::Columns(2);
        ImGui::TextUnformatted(label.c_str());
		ImGui::NextColumn();
		ImGui::PushItemWidth(-1);
		ImGui::PushID(label.c_str());

		if (ImGui::DragScalarN("", ImGuiDataType_Float, value, 3, speed, &min, &max, format))
            setter((Vector3){value[0], value[1], value[2]});

		ImGui::PopID();
		ImGui::PopItemWidth();
		ImGui::NextColumn();
        ImGui::Columns();
    }

    void UIElement::ColorField(const std::string &label, Color (*getter)(void), void (*setter)(Color))
    {
        Color col = getter();
        float value[4] = {(float) col.r, (float) col.g, (float) col.b, (float) col.a};

        ImGui::Columns(2);
        ImGui::TextUnformatted(label.c_str());
		ImGui::NextColumn();
		ImGui::PushItemWidth(-1);
		ImGui::PushID(label.c_str());

		if (ImGui::ColorEdit4("", value))
            setter((Color){(unsigned char) value[0], (unsigned char) value[1], (unsigned char) value[2], (unsigned char) value[3]});

		ImGui::PopID();
		ImGui::PopItemWidth();
		ImGui::NextColumn();
        ImGui::Columns();
    }
}
