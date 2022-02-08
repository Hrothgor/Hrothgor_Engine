/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** UIElement
*/

#include "UIElement.hpp"

namespace hr {
    void UIElement::StartField(const std::string &label)
    {
        ImGui::Columns(2);
        ImGui::TextUnformatted(label.c_str());
		ImGui::PushItemWidth(-1);
		ImGui::NextColumn();
		ImGui::PushItemWidth(-1);
        ImGui::PushID(label.c_str());
    }

    void UIElement::EndField()
    {
        ImGui::PopID();
		ImGui::PopItemWidth();
		ImGui::NextColumn();
        ImGui::Columns();
    }

    void UIElement::CheckBox(const std::string &label, std::function<bool()> getter, std::function<void(bool)> setter)
    {
        StartField(label);
        
        bool value = getter();
    
        if (ImGui::Checkbox("", &value))
            setter(value);

        EndField();
    }

    void UIElement::SliderFloatField(const std::string &label, std::function<float()> getter, std::function<void(float)> setter, float min, float max, const char* format, float power)
    {
        StartField(label);

        float value = getter();

		if (ImGui::SliderScalarN("", ImGuiDataType_Float, &value, 1, &min, &max, format, power))
            setter(value);
        
		EndField();
    }

    void UIElement::EnumField(const std::string &label, std::function<int()> getter, std::function<void(int)> setter, std::vector<std::string> list)
    {
        StartField(label);

        int value = getter();

        if (ImGui::BeginCombo("", list[value].c_str())) {
            for (unsigned int n = 0; n < list.size(); n++)
            {
                bool is_selected = (value == (int)n);
                if (ImGui::Selectable(list[n].c_str(), is_selected))
                    setter(n);
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }
        
		EndField();
    }

    void UIElement::IntField(const std::string &label, std::function<int()> getter, std::function<void(int)> setter, float speed, float min, float max, const char* format)
    {
        StartField(label);

        int value = getter();

		if (ImGui::DragScalarN("", ImGuiDataType_S32, &value, 1, speed, &min, &max, format))
            setter(value);

		EndField();
    }

    void UIElement::FloatField(const std::string &label, std::function<float()> getter, std::function<void(float)> setter, float speed, float min, float max, const char* format)
    {
        StartField(label);

        float value = getter();

		if (ImGui::DragScalarN("", ImGuiDataType_Float, &value, 1, speed, &min, &max, format))
            setter(value);

		EndField();
    }

    void UIElement::Vector2Field(const std::string &label, std::function<Vector2()> getter, std::function<void(Vector2)> setter, float speed, float min, float max, const char* format)
    {
        StartField(label);

        Vector2 vec = getter();
        float value[2] = {vec.x, vec.y};

		if (ImGui::DragScalarN("", ImGuiDataType_Float, value, 2, speed, &min, &max, format))
            setter((Vector2){value[0], value[1]});

		EndField();
    }

    void UIElement::Vector3Field(const std::string &label, std::function<Vector3()> getter, std::function<void(Vector3)> setter, float speed, float min, float max, const char* format)
    {
        StartField(label);

        Vector3 vec = getter();
        float value[3] = {vec.x, vec.y, vec.z};

		if (ImGui::DragScalarN("", ImGuiDataType_Float, value, 3, speed, &min, &max, format))
            setter((Vector3){value[0], value[1], value[2]});

		EndField();
    }

    void UIElement::ColorField(const std::string &label, std::function<Color()> getter, std::function<void(Color)> setter)
    {
        StartField(label);

        Color col = getter();
        Vector4 nCol = ColorNormalize(col);
        float value[4] = {nCol.x, nCol.y, nCol.z, nCol.w};


		if (ImGui::ColorEdit4("", value))
            setter(ColorFromNormalized((Vector4){value[0], value[1], value[2], value[3]}));

		EndField();
    }

    void UIElement::StringField(const std::string &label, std::function<std::string()> getter, std::function<void(std::string)> setter)
    {
        StartField(label);

        std::string path = getter();
        char buf[100]{};
        std::memcpy(buf, path.data(), path.size());

		if (ImGui::InputText("", buf, IM_ARRAYSIZE(buf)))
            setter(std::string(buf));

		EndField();
    }
}
