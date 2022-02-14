/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** AssetsPanel
*/

#include "AssetsPanel.hpp"
#include "../../../Ecs/Engine.hpp"

namespace hr {
    AssetsPanel::AssetsPanel()
    {
    }

    AssetsPanel::~AssetsPanel()
    {
    }

    void AssetsPanel::Start()
    {
    }

    void AssetsPanel::ImGuiRender()
    {
        ImGui::Begin("Assets", &_isOpen);

        if (Engine::Get()->GetProjectName() == "") {
            ImGui::TextUnformatted("No project loaded !");
            ImGui::End();
            return;
        }

        bool isFocus = ImGui::IsWindowFocused();
        ActiveEvent(!isFocus);

        ImGui::Columns(2);

        ImGuiTreeNodeFlags rootNodeFlags = (ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_SpanFullWidth);

        std::string projectPath = "Projects/" + Engine::Get()->GetProjectName() + "/";

		if (_selectedDir == projectPath + "Assets")
			rootNodeFlags |= ImGuiTreeNodeFlags_Selected;

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0.0f, 0.0f });
        bool nodeIsOpen = ImGui::TreeNodeEx("##AssetsRootTreeNode", rootNodeFlags, "Assets");
        ImGui::PopStyleVar();

        if (ImGui::IsItemClicked())
			_selectedDir = projectPath + "Assets";

        if (nodeIsOpen) {
            DirectoryDraw(projectPath + "Assets");
            ImGui::TreePop();
        }

        ThumbnailsDraw();

        ImGui::Columns(1);
		ImGui::End();
    }

    void AssetsPanel::DirectoryDraw(const std::string &path)
    {
        std::vector<std::string> dirList = GetDirNames(path);

        for (std::string dir : dirList) {
            bool entityIsParent = GetDirNames(dir).size();
            ImGuiTreeNodeFlags nodeFlags = ImGuiTreeNodeFlags_AllowItemOverlap;

			if (_selectedDir == dir)
				nodeFlags |= ImGuiTreeNodeFlags_Selected;

            if (!entityIsParent)
				nodeFlags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
            
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0.0f, 0.0f });
            bool nodeIsOpen = ImGui::TreeNodeEx(("##TreeNode" + dir).c_str(), nodeFlags, "%s", dir.substr((dir.find_last_of("/")) + 1).c_str());
            ImGui::PopStyleVar();

            if (ImGui::IsItemClicked())
                _selectedDir = dir;

            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0.0f, 0.0f });
			ImGui::InvisibleButton("ENTITY_REORDER", { -1, 5 });
			ImGui::PopStyleVar();

            if (entityIsParent && nodeIsOpen)
			{
				DirectoryDraw(dir);
				ImGui::TreePop();
			}
        }
    }

    std::vector<std::string> AssetsPanel::GetDirNames(const std::string &path)
    {
        std::vector<std::string> dirList;
        
        for (const auto &entry : std::filesystem::directory_iterator(path))
            if (std::filesystem::is_directory(entry.symlink_status()))
                dirList.push_back(entry.path().string());
        return dirList;
    }

    void AssetsPanel::ThumbnailsDraw()
    {
        static bool firstCall = true;

        if (firstCall)
        {
            ImGui::SetColumnWidth(0, 250.0f);
            firstCall = false;
        }
        ImGui::NextColumn();

        ImGui::PushItemWidth(-1);
        ImGui::Spacing();
        {
            int tSize = _thumbnailSize;
            if (ImGui::SliderInt("##Thumbnail Size", &tSize, 50, 248, "Thumbnail Size : %dpx"))
                _thumbnailSize = tSize;
        }
        ImGui::PopItemWidth();
    }

    void AssetsPanel::End()
    {

    }
}