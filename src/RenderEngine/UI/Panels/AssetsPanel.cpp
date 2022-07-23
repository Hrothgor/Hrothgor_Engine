/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** AssetsPanel
*/

#include "AssetsPanel.hpp"
#include "Ecs/Engine.hpp"
#include "RenderEngine/AssetsManager.hpp"
#include "Tools/String.hpp"

namespace hr {
    AssetsPanel::AssetsPanel()
    {
    }

    AssetsPanel::~AssetsPanel()
    {
    }

    void AssetsPanel::Start()
    {
        _selectedDir = "Engine";
    }

    void AssetsPanel::ImGuiRender()
    {
        ImGui::Begin("Assets", &_isOpen);

        bool isFocus = ImGui::IsWindowFocused();
        ActiveEvent(!isFocus);

        ImGui::Columns(2);

        ImGuiTreeNodeFlags rootNodeFlags = (ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_SpanFullWidth | ImGuiTreeNodeFlags_DefaultOpen);

        std::string projectPath = "Engine";

		if (_selectedDir == projectPath)
			rootNodeFlags |= ImGuiTreeNodeFlags_Selected;

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0.0f, 0.0f });
        bool nodeIsOpen = ImGui::TreeNodeEx("##EngineRootTreeNode", rootNodeFlags, "Engine");
        ImGui::PopStyleVar();

        if (ImGui::IsItemClicked())
			_selectedDir = projectPath;

        if (nodeIsOpen) {
            DirectoryDraw(projectPath);
            ImGui::TreePop();
        }

        //////////////////////////////////////////////////////
		// Thumbnail /////////////////////////////////////////
		//////////////////////////////////////////////////////

        static bool firstCall = true;

        if (firstCall)
        {
            ImGui::SetColumnWidth(0, 250.0f);
            firstCall = false;
        }
        if (_selectedDir != "") {
            ImGui::NextColumn();

            ImGui::PushItemWidth(-1);
            ImGui::Spacing();
            {
                int tSize = _thumbnailSize;
                if (ImGui::SliderInt("##Thumbnail Size", &tSize, 50, 248, "Thumbnail Size : %dpx"))
                    _thumbnailSize = tSize;
            }
            ImGui::PopItemWidth();

            if (_selectedDir != "")
			{
				if (ImGui::ArrowButton("AssetThumbnailUpFolderButton", ImGuiDir_Up))
				{
					std::string parentPath = _selectedDir;
					parentPath = parentPath.substr(0, parentPath.find_last_of('/'));
					if (parentPath.empty())
						parentPath = "Engine";
                    _selectedDir = parentPath;
				}

				ImGui::SameLine();
				ImGui::TextUnformatted(_selectedDir.c_str());
			}

            ImGui::BeginChild("##ThumbnailView", { 0, 0 }, false, ImGuiWindowFlags_AlwaysUseWindowPadding);

            std::vector<std::string> selectionFolder = GetDirNames(_selectedDir, false);

            uint32_t count = selectionFolder.size();
            uint32_t n = 0;
            if (count > 0)
            {
                for (const auto& assetPath : selectionFolder)
                {
                    ImGui::PushID(n);
                    ThumbnailDraw(assetPath, n + 1 == count);
                    ImGui::PopID();
                    n++;
                }
            }
            ImGui::EndChild();
        }

        ImGui::Columns(1);
		ImGui::End();
    }

    void AssetsPanel::DirectoryDraw(const std::string &path)
    {
        std::vector<std::string> dirList = GetDirNames(path, true);

        for (std::string dir : dirList) {
            bool entityIsParent = GetDirNames(dir, true).size();
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

    std::vector<std::string> AssetsPanel::GetDirNames(const std::string &path, bool onlyDir)
    {
        std::vector<std::string> dirList;
        
        for (const auto &entry : std::filesystem::directory_iterator(path))
            if (onlyDir) {
                if (std::filesystem::is_directory(entry.symlink_status()))
                    dirList.push_back(entry.path().string());
            } else {
                dirList.push_back(entry.path().string());
            }
        return dirList;
    }

    void AssetsPanel::ThumbnailDraw(const std::string &path, bool last)
    {
        ImVec2 thumbnailSize{ (float)_thumbnailSize, (float)_thumbnailSize };

        // Texture2D icon = LoadTexture("Engine/Ressources/Icons/file-icon.png");
        Texture2D *icon = nullptr;
        if (std::filesystem::is_directory(path)) {
            icon = AssetsManager::Get()->GetTextureAddr("Engine/Ressources/Icons/folder.png");
        } else if (String::EndWith(path, ".obj")) {
            icon = AssetsManager::Get()->GetTextureAddr("Engine/Ressources/Icons/file-obj.png");
        } else if (String::EndWith(path, ".scn")) {
            icon = AssetsManager::Get()->GetTextureAddr("Engine/Ressources/Icons/scene.png");
        } else if (String::EndWith(path, ".png")) {
            icon = AssetsManager::Get()->GetTextureAddr(path);
        } else {
            icon = AssetsManager::Get()->GetTextureAddr("Engine/Ressources/Icons/file.png");
        }

        ImGui::PushStyleColor(ImGuiCol_Button,        { 0.2f, 0.2f, 0.2f, 0.2f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.2f, 0.2f, 0.2f, 0.5f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive,  { 0.2f, 0.2f, 0.2f, 0.7f });

        if (icon) {
            ImGui::ImageButton((ImTextureID)icon, thumbnailSize);
        } else {
            ImGui::Button("", thumbnailSize);
        }
        ImGui::PopStyleColor(3);

        if (ImGui::IsItemClicked() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
		{
            if (std::filesystem::is_directory(path))
                _selectedDir = path;
		}

        if (ImGui::IsItemHovered()) {
            ImGui::BeginTooltip();
            ImGui::TextUnformatted(String::NameByPath(path).c_str());
            ImGui::EndTooltip();
        }

        //////////////////////////////////////////////////////
		// DragPayload ///////////////////////////////////////
		//////////////////////////////////////////////////////

        // I drag and drop the path (str), but I could drag and drop the model or texture directly

        if (String::EndWith(path, ".png") || String::EndWith(path, ".obj") || String::EndWith(path, ".scn")) {
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 10.0f, 10.0f });
            if (ImGui::BeginDragDropSource())
            {
                if (String::EndWith(path, ".png")) {
                    ImGui::SetDragDropPayload("TEXTURE_PAYLOAD", path.c_str(), path.size() + 1);
                } else if (String::EndWith(path, ".obj")) {
                    ImGui::SetDragDropPayload("MODEL_PAYLOAD", path.c_str(), path.size() + 1);
                } else if (String::EndWith(path, ".scn")) {
                    ImGui::SetDragDropPayload("SCENE_PAYLOAD", path.c_str(), path.size() + 1);
                }

                ImGui::TextUnformatted(String::NameByPath(path).c_str());
                ImGui::Image((ImTextureID)icon, { 128, 128 });

                ImGui::EndDragDropSource();
            }
            ImGui::PopStyleVar();
        }

        //////////////////////////////////////////////////////
		// Text //////////////////////////////////////////////
		//////////////////////////////////////////////////////

		ImDrawList& windowDrawList = *ImGui::GetWindowDrawList();

		ImVec2 rectMin = ImGui::GetItemRectMin();
		ImVec2 rectSize = ImGui::GetItemRectSize();
		ImVec2 textSize = ImGui::CalcTextSize(String::NameByPath(path).c_str());

		static Vector2 padding{ 5, 5 };
		static int marginTop = 15;

		if (textSize.x + padding.x * 2 <= rectSize.x) // Enough space
		{
			/*
			<----------> = rectSize.x
			rectMin
			||
			\/
			*___________
			|    O     | /\
			|  --|--   | ||	                             // Closer look to the text
			|    |     | || = rectSize.y                 __________
			|   / \    | ||                              |        | => padding.y
			|__________| \/     \/                       | Player |
			                    || = marginTop           |________| => padding.y
			  |Player|          /\                       ||      ||
			                                             \/      \/
			  <------> = textSize.x                  padding.x   padding.x
			| |
			<-> = (rectSize.x - textSize.x) / 2
			*/

			float rectMin_x = rectMin.x - padding.x + (rectSize.x - textSize.x) / 2;
			float rectMin_y = rectMin.y + rectSize.y + marginTop;

			float rectMax_x = rectMin_x + textSize.x + padding.x * 2;
			float rectMax_y = rectMin_y + textSize.y + padding.y * 2;

			windowDrawList.AddRectFilled({ rectMin_x, rectMin_y }, { rectMax_x, rectMax_y }, ImColor(20, 20, 20), 5);
			windowDrawList.AddText({ rectMin_x + padding.x, rectMin_y + padding.y }, ImColor(1.0f, 1.0f, 1.0f), String::NameByPath(path).c_str());
		}
		else // Tight => use ellipsis
		{
			float rectMin_y = rectMin.y + rectSize.y + marginTop;

			float rectMax_x = rectMin.x + rectSize.x;
			float rectMax_y = rectMin_y + textSize.y + padding.y * 2;

			windowDrawList.AddRectFilled({ rectMin.x, rectMin_y }, { rectMax_x, rectMax_y }, ImColor(20, 20, 20), 5);

			rectMax_x -= padding.x;
			rectMax_y -= padding.y;

			ImGui::RenderTextEllipsis(&windowDrawList, { rectMin.x + padding.x, rectMin_y + padding.y }, { rectMax_x, rectMax_y }, rectMax_x, rectMax_x, String::NameByPath(path).c_str(), nullptr, &textSize);
		}
        
        //////////////////////////////////////////////////////
		// Wrapping //////////////////////////////////////////
		//////////////////////////////////////////////////////

		float nextBtn = ImGui::GetItemRectMax().x + ImGui::GetStyle().ItemSpacing.x + rectSize.x;
		float rightMost = ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x;

		if (!last && nextBtn < rightMost)
			ImGui::SameLine();
		else
			ImGui::Dummy({ 0, 50 });
    }

    void AssetsPanel::End()
    {

    }
}