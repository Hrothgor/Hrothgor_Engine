/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** InspectorPanel
*/

#ifndef INSPECTORPANEL_HPP_
#define INSPECTORPANEL_HPP_

#include "include.hpp"
#include "ImGuiPanel.hpp"
#include "../../../Ecs/GameObject.hpp"

namespace hr {
    class InspectorPanel : public ImGuiPanel {
        public:
            InspectorPanel();
            ~InspectorPanel();
                
            virtual void ImGuiRender() override;

            template <typename Comp>
            void ImGuiRenderComponent(GameObject *entity) 
            {
                Comp *comp = entity->GetComponent<Comp>();

                ImGui::PushID(("##button" + std::string(typeid(Comp).name())).c_str());
                if (ImGui::Button("X"))
                {
                    entity->RemoveComponent<Comp>();
                    ImGui::PopID();
                    return;
                }
                ImGui::PopID();

                ImGui::SameLine();

                ImGui::PushID(("##checkbox" + std::string(typeid(Comp).name())).c_str());
                bool value = comp->IsActive();
                if (ImGui::Checkbox("", &value))
                    comp->SetActive(value);
                ImGui::PopID();

                ImGui::SameLine();

                if (ImGui::ArrowButton(("##arrowUp" + std::string(typeid(Comp).name())).c_str(), ImGuiDir_Up)) {
                    auto componentsList = entity->GetComponents();
                    auto it = std::find_if(componentsList.begin(), componentsList.end(),
                            [&](const std::pair<std::type_index, Component *> &element){ return element.first == typeid(Comp);} );
                    if (it != componentsList.begin())
                    {
                        auto cpy = componentsList[it - componentsList.begin()];
                        componentsList[it - componentsList.begin()] = componentsList[it - componentsList.begin() - 1];
                        componentsList[it - componentsList.begin() - 1] = cpy;
                        entity->SetComponents(componentsList);
                    }
                }

                ImGui::SameLine();
                
                if (ImGui::ArrowButton(("##arrowDown" + std::string(typeid(Comp).name())).c_str(), ImGuiDir_Down))
                {
                    auto componentsList = entity->GetComponents();
                    auto it = std::find_if(componentsList.begin(), componentsList.end(),
                            [&](const std::pair<std::type_index, Component *> &element){ return element.first == typeid(Comp);} );
                    if (it != componentsList.end() - 1)
                    {
                        auto cpy = componentsList[it - componentsList.begin()];
                        componentsList[it - componentsList.begin()] = componentsList[it - componentsList.begin() + 1];
                        componentsList[it - componentsList.begin() + 1] = cpy;
                        entity->SetComponents(componentsList);
                    }
                }

                ImGui::SameLine();

                ImGui::SetNextItemOpen(true, ImGuiCond_Once);
                if (ImGui::CollapsingHeader(comp->GetName().c_str())) {
                    comp->ImGuiRender();
                    ImGui::Separator();
                }
            }

            template <typename Comp>
            void ImGuiRenderAddComponent(const std::string &label, GameObject *entity) 
            {
                if (ImGui::Selectable(label.c_str()))
                    entity->AddComponent<Comp>();
            }
        protected:
        private:
    };
}

#endif /* !INSPECTORPANEL_HPP_ */
