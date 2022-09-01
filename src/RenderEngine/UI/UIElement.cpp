/*
** EPITECH PROJECT, 2022
** Hrothgor_Engine
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

    void UIElement::Header(const std::string &label)
    {
        ImGui::SetWindowFontScale(1.5);
        ImGui::TextColored(ImVec4(9.0 / 255, 94.0 / 255, 149.0 / 255, 1), "%s", label.c_str());
        ImGui::SetWindowFontScale(1);
    }

    void UIElement::CheckBox(const std::string &label, bool &val)
    {
        StartField(label);
        
        bool value = val;
    
        if (ImGui::Checkbox("", &value))
            val = value;

        EndField();
    }

    void UIElement::SliderFloatField(const std::string &label, float &val, float min, float max, const char* format, float power)
    {
        StartField(label);

        float value = val;

		if (ImGui::SliderScalarN("", ImGuiDataType_Float, &value, 1, &min, &max, format, power))
            val = value;
        
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

    void UIElement::IntField(const std::string &label, int &val, float speed, int min, int max, const char* format)
    {
        StartField(label);

        int value = val;

		if (ImGui::DragScalarN("", ImGuiDataType_S32, &value, 1, speed, &min, &max, format))
            val = value;

		EndField();
    }

    void UIElement::FloatField(const std::string &label, float &val, float speed, float min, float max, const char* format)
    {
        StartField(label);

        float value = val;

		if (ImGui::DragScalarN("", ImGuiDataType_Float, &value, 1, speed, &min, &max, format))
            val = value;

		EndField();
    }

    void UIElement::Vector2Field(const std::string &label, Vector2 &val, float speed, float min, float max, const char* format)
    {
        StartField(label);

        Vector2 vec = val;
        float value[2] = {vec.x, vec.y};

		if (ImGui::DragScalarN("", ImGuiDataType_Float, value, 2, speed, &min, &max, format))
            val = (Vector2){value[0], value[1]};

		EndField();
    }

    void UIElement::Vector3Field(const std::string &label, Vector3 &val, float speed, float min, float max, const char* format)
    {
        StartField(label);

        Vector3 vec = val;
        float value[3] = {vec.x, vec.y, vec.z};

		if (ImGui::DragScalarN("", ImGuiDataType_Float, value, 3, speed, &min, &max, format))
            val = (Vector3){value[0], value[1], value[2]};

		EndField();
    }

    void UIElement::ColorField(const std::string &label, Color &val)
    {
        StartField(label);

        Color col = val;
        Vector4 nCol = ColorNormalize(col);
        float value[4] = {nCol.x, nCol.y, nCol.z, nCol.w};


		if (ImGui::ColorEdit4("", value))
            val = ColorFromNormalized((Vector4){value[0], value[1], value[2], value[3]});

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

    void UIElement::ModelField(const std::string &label, std::function<std::string()> getter, std::function<void(std::string)> setter)
    {
        StartField(label);

        std::string path = getter();
        char buf[100]{};
        std::memcpy(buf, path.data(), path.size());

		ImGui::InputText("", buf, IM_ARRAYSIZE(buf), ImGuiInputTextFlags_ReadOnly);

        if (ImGui::BeginDragDropTarget())
        {
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("MODEL_PAYLOAD"))
            {
                char *path = static_cast<char *>(payload->Data);
                setter(std::string(path));
            }
            ImGui::EndDragDropTarget();
        }

		EndField();
    }

    void UIElement::TextureField(const std::string &label, std::function<std::string()> getter, std::function<void(std::string)> setter)
    {
        StartField(label);

        std::string path = getter();
        char buf[100]{};
        std::memcpy(buf, path.data(), path.size());

		ImGui::InputText("", buf, IM_ARRAYSIZE(buf), ImGuiInputTextFlags_ReadOnly);

        if (ImGui::BeginDragDropTarget())
        {
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("TEXTURE_PAYLOAD"))
            {
                char *path = static_cast<char *>(payload->Data);
                setter(std::string(path));
            }
            ImGui::EndDragDropTarget();
        }

		EndField();
    }
}
