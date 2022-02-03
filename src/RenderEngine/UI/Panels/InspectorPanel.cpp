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

namespace hr {
    InspectorPanel::InspectorPanel()
    {
    }

    InspectorPanel::~InspectorPanel()
    {
    }

    void InspectorPanel::ImGuiRender()
    {
        ImGui::SetNextWindowPos(ImVec2(WIDTH - 450, 0));
        ImGui::SetNextWindowSize(ImVec2(450, HEIGHT));
        ImGui::Begin("Inspector", &_isOpen, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
        ImGui::SetWindowFontScale(1.2);

        GameObject *entity = nullptr;
		if ((entity = Engine::Get()->GetSelectedEntity()))
		{

            {
                ImGui::PushID("activation");
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

                ImGui::InputText("", buf, IM_ARRAYSIZE(buf));
                entity->SetName(buf);
                
                ImGui::PopID();
            }
        
			ImGui::Text("UUID: %s", entity->GetUUID().str().data());

			bool wannaDestroy = false;
			if (ImGui::Button("Destroy Entity"))
				wannaDestroy = true;

			ImGui::Separator();

            entity->GetTransform()->ImGuiRender();

// 			for (const auto& componentTypeID : entity.GetComponentsTypeIDList())
// 			{
// 				CheckComponentEditor<TransformComponent>(componentTypeID, entity);
// 				CheckComponentEditor<SpriteRendererComponent>(componentTypeID, entity);
// 				CheckComponentEditor<CameraComponent>(componentTypeID, entity);
// 				CheckComponentEditor<RigidBody2DComponent>(componentTypeID, entity);
// 				CheckComponentEditor<Colliders2DComponent>(componentTypeID, entity);
// 			}

// //			if (ImGui::Button("Add Component##Button", ImVec2(-1.0f, 40.0f)))
// 			if (ImGui::Button("Add Component##Button"))
// 				ImGui::OpenPopup("Add Component##Popup");

// 			if (ImGui::BeginPopup("Add Component##Popup"))
// 			{
// 				CheckAddComponent<TransformComponent>(entity, "Transform##AddComponentPopup");
// 				CheckAddComponent<SpriteRendererComponent>(entity, "SpriteRenderer##AddComponentPopup", nullptr);
// 				CheckAddComponent<CameraComponent>(entity, "Camera##AddComponentPopup");
// 				CheckAddComponent<RigidBody2DComponent>(entity, "RigidBody2D##AddComponentPopup");
// 				CheckAddComponent<Colliders2DComponent>(entity, "Colliders2D##AddComponentPopup");

// 				ImGui::EndPopup();
// 			}


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
        

        // ImGui::Begin("Inspector");
        // for (auto [type, comp] : _components)
        //     if (comp->IsActive())
        //         comp->ImGuiRender();
        // ImGui::End();
    }
}
