/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** InspectorPanel
*/

#include "InspectorPanel.hpp"
#include "../../../Ecs/Engine.hpp"
#include "../../../Ecs/GameObject.hpp"

#include "../../../Components/Transform.hpp"
#include "../../../Components/Light.hpp"
#include "../../../Components/MeshRenderer.hpp"
#include "../../../Components/MainCamera3D.hpp"

namespace hr {
    InspectorPanel::InspectorPanel()
    {
    }

    InspectorPanel::~InspectorPanel()
    {
    }

    void InspectorPanel::ImGuiRender()
    {
        ImGui::Begin("Inspector", &_isOpen);

        GameObject *entity = nullptr;
		if ((entity = Engine::Get()->GetSelectedEntity()))
		{

            {
                ImGui::PushID("##checkbox");
                bool value = entity->IsActive();
                if (ImGui::Checkbox("", &value))
                    entity->SetActive(value);
                ImGui::PopID();

                ImGui::SameLine();
                ImGui::Text("Name: ");
                ImGui::SameLine();

                
                char buf[100]{};
                std::memcpy(buf, entity->GetName().data(), entity->GetName().size());
                ImGui::PushID(entity->GetUUID().str().data());

                if (ImGui::InputText("", buf, IM_ARRAYSIZE(buf)))
                    entity->SetName(buf);
                
                ImGui::PopID();
            }
        
			ImGui::Text("UUID: %s", entity->GetUUID().str().data());

			bool wannaDestroy = false;
			if (ImGui::Button("Destroy Entity"))
				wannaDestroy = true;

			ImGui::Separator();

            ImGui::PushID(("##collapsingHeader" + entity->GetUUID().str()).c_str());
            ImGui::SetNextItemOpen(true, ImGuiCond_Once);
            if (ImGui::CollapsingHeader(entity->GetTransform()->GetName().c_str())) {
                entity->GetTransform()->ImGuiRender();
                ImGui::Separator();
            }
            ImGui::PopID();

            auto entityComponents = entity->GetComponents();
            for (auto [compId, comp] : entityComponents) {
                if (entity->HasComponentId<Transform>(compId)) { ImGuiRenderComponent<Transform>(entity); continue; }
                if (entity->HasComponentId<Light>(compId)) { ImGuiRenderComponent<Light>(entity); continue; }
                if (entity->HasComponentId<MeshRenderer>(compId)) { ImGuiRenderComponent<MeshRenderer>(entity); continue; }
                if (entity->HasComponentId<MainCamera3D>(compId)) { ImGuiRenderComponent<MainCamera3D>(entity); continue; }
            }

            if (ImGui::Button("Add Component##Button", ImVec2(-1.0f, 40.0f)))
				ImGui::OpenPopup("Add Component##Popup");

			if (ImGui::BeginPopup("Add Component##Popup"))
			{
                if (!entity->HasComponent<Light>()) { ImGuiRenderAddComponent<Light>("Light", entity); }
                if (!entity->HasComponent<MeshRenderer>()) { ImGuiRenderAddComponent<MeshRenderer>("MeshRenderer", entity); }
                if (!entity->HasComponent<MainCamera3D>()) { ImGuiRenderAddComponent<MainCamera3D>("MainCamera3D", entity); }
				ImGui::EndPopup();
			}
    

			if (wannaDestroy)
			{
				Engine::Get()->SetSelectedEntity(nullptr);
				Engine::Get()->Destroy(entity);
			}
		}
		else
		{
			ImGui::TextUnformatted("Please select some thing to edit!");
		}

		ImGui::End();
    }
}