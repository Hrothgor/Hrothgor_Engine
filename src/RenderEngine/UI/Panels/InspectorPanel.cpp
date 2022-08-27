/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** InspectorPanel
*/

#include "InspectorPanel.hpp"
#include "Ecs/Engine.hpp"
#include "Ecs/GameObject.hpp"

#include "Components/Transform.hpp"
#include "Components/Light.hpp"
#include "Components/MeshRenderer.hpp"
#include "Components/Collider/BoxCollider.hpp"
#include "Components/Collider/SphereCollider.hpp"
#include "Components/MainCamera3D.hpp"
#include "Components/RigidBody.hpp"
#include "Components/Particles/ParticleSystem.hpp"

#include "Components/Custom/SphereSender.hpp"

namespace hr {
    InspectorPanel::InspectorPanel()
    {
    }

    InspectorPanel::~InspectorPanel()
    {
    }

    void InspectorPanel::Start()
    {
    }

    void InspectorPanel::ImGuiRender()
    {
        ImGui::Begin("Inspector", &_isOpen);

        if (Engine::Get()->GetProjectName() == "") {
            ImGui::TextUnformatted("No project loaded !");
            ImGui::End();
            return;
        }

        bool isFocus = ImGui::IsWindowFocused();
        ActiveEvent(!isFocus);

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
            for (auto [compId, comp] : entityComponents) { // for is to keep order
                if (entity->HasComponentId<Transform>(compId)) { ImGuiRenderComponent<Transform>(entity); continue; }
                if (entity->HasComponentId<Light>(compId)) { ImGuiRenderComponent<Light>(entity); continue; }
                if (entity->HasComponentId<MeshRenderer>(compId)) { ImGuiRenderComponent<MeshRenderer>(entity); continue; }
                if (entity->HasComponentId<BoxCollider>(compId)) { ImGuiRenderComponent<BoxCollider>(entity); continue; }
                if (entity->HasComponentId<SphereCollider>(compId)) { ImGuiRenderComponent<SphereCollider>(entity); continue; }
                if (entity->HasComponentId<RigidBody>(compId)) { ImGuiRenderComponent<RigidBody>(entity); continue; }
                if (entity->HasComponentId<ParticleSystem>(compId)) { ImGuiRenderComponent<ParticleSystem>(entity); continue; }
                if (entity->HasComponentId<SphereSender>(compId)) { ImGuiRenderComponent<SphereSender>(entity); continue; }
            }

            if (ImGui::Button("Add Component##Button", ImVec2(-1.0f, 40.0f)))
				ImGui::OpenPopup("Add Component##Popup");

			if (ImGui::BeginPopup("Add Component##Popup"))
			{
                if (!entity->HasComponent<Light>()) { ImGuiRenderAddComponent<Light>("Light", entity); }
                if (!entity->HasComponent<MeshRenderer>()) { ImGuiRenderAddComponent<MeshRenderer>("MeshRenderer", entity); }
                if (!entity->HasComponent<BoxCollider>()) { ImGuiRenderAddComponent<BoxCollider>("BoxCollider", entity); }
                if (!entity->HasComponent<SphereCollider>()) { ImGuiRenderAddComponent<SphereCollider>("SphereCollider", entity); }
                if (!entity->HasComponent<RigidBody>()) { ImGuiRenderAddComponent<RigidBody>("RigidBody", entity); }
                if (!entity->HasComponent<ParticleSystem>()) { ImGuiRenderAddComponent<ParticleSystem>("ParticleSystem", entity); }
                if (!entity->HasComponent<SphereSender>()) { ImGuiRenderAddComponent<SphereSender>("SphereSender", entity); }
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
			ImGui::TextUnformatted("Please select some thing to edit !");
		}

		ImGui::End();
    }

    void InspectorPanel::End()
    {

    }
}
