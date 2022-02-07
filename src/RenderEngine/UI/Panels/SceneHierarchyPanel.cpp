/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** SceneHierarchyPanel
*/

#include "SceneHierarchyPanel.hpp"
#include "../../../Ecs/Engine.hpp"
#include "../../../Ecs/GameObject.hpp"

namespace hr {
    SceneHierarchyPanel::SceneHierarchyPanel()
    {
    }

    SceneHierarchyPanel::~SceneHierarchyPanel()
    {
    }

    void SceneHierarchyPanel::Start()
    {
    }

    void SceneHierarchyPanel::ImGuiRender()
    {
        ImGui::Begin("Scene Hierarchy", &_isOpen);

        EntityDraw(nullptr);
        
        ImGui::BeginChild("Blank Space");
        {
            if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) && ImGui::IsWindowHovered())
                Engine::Get()->SetSelectedEntity(nullptr);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 5.0f, 5.0f });
            if (ImGui::BeginPopupContextWindow("_SCENE_HIERARCHY_CONTEXTMENU"))
            {
                if (ImGui::MenuItem("Create Empty Entity"))
                    Engine::Get()->CreateEmptyGameObject();
                ImGui::EndPopup();
            }
            ImGui::PopStyleVar();
        }
        ImGui::EndChild();

        if (ImGui::BeginDragDropTarget())
        {
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("_SCENE_HIERARCHY_ENTITY_DRAG"))
            {
                GameObject *cpy = static_cast<GameObject *>(payload->Data);
                GameObject *ent = Engine::Get()->Find(cpy->GetUUID());
                ent->DetachFromParent();
            }
            ImGui::EndDragDropTarget();
        }

        ImGui::End();
    }

    void SceneHierarchyPanel::EntityDraw(GameObject *parent)
    {
        std::vector<GameObject *> entityList = parent ? parent->GetChilds() : Engine::Get()->GetRootEntities();

        for (GameObject *entity : entityList) {
            bool entityIsParent = entity->GetChilds().size();
            ImGuiTreeNodeFlags nodeFlags = ImGuiTreeNodeFlags_AllowItemOverlap;

			if (Engine::Get()->GetSelectedEntity() == entity)
				nodeFlags |= ImGuiTreeNodeFlags_Selected;

            if (!entityIsParent)
				nodeFlags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
            
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0.0f, 0.0f });
            bool nodeIsOpen = ImGui::TreeNodeEx((void *)entity, nodeFlags, "%s", entity->GetName().c_str());
            ImGui::PopStyleVar();

            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 10.0f, 10.0f });
			if (ImGui::BeginDragDropSource())
			{
				ImGui::SetDragDropPayload("_SCENE_HIERARCHY_ENTITY_DRAG", entity, sizeof(GameObject));
				ImGui::TextUnformatted(entity->GetName().c_str());
				ImGui::EndDragDropSource();
			}
			ImGui::PopStyleVar();

            if (ImGui::BeginDragDropTarget())
			{
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("_SCENE_HIERARCHY_ENTITY_DRAG"))
				{
                    GameObject *cpy = static_cast<GameObject *>(payload->Data);
					GameObject *ent = Engine::Get()->Find(cpy->GetUUID());
                    ent->SetParent(entity);
				}
				ImGui::EndDragDropTarget();
			}

            if (ImGui::IsItemClicked())
                Engine::Get()->SetSelectedEntity(entity);

            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0.0f, 0.0f });
			ImGui::InvisibleButton("ENTITY_REORDER", { -1, 5 });
			ImGui::PopStyleVar();

            // if (ImGui::BeginDragDropTarget())
			// {
			// 	if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("_SCENE_HIERARCHY_ENTITY_DRAG"))
			// 	{
			// 		std::cout << "DeplaceEntity" << std::endl;
			// 	}
			// 	ImGui::EndDragDropTarget();
			// }
            
            if (entityIsParent && nodeIsOpen)
			{
				EntityDraw(entity);
				ImGui::TreePop();
			}
        }
    }

    void SceneHierarchyPanel::End()
    {
    }
}
