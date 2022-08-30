/*
** EPITECH PROJECT, 2022
** Hrothgor_Engine
** File description:
** MeshRenderer
*/

#ifndef MESHRENDERER_HPP_
#define MESHRENDERER_HPP_

#include "Include.hpp"
#include "Ecs/Component.hpp"
#include "Json.hpp"

namespace hr {
    class MeshRenderer : public Component {
        public:
            MeshRenderer(GameObject *gameObject);
            ~MeshRenderer();

            virtual void Update() override;

            Texture2D GetTexture() const;
            std::string GetTexturePath() const;
            void LoadTextureFromPath(const std::string &path);

            Model GetModel() const;
            std::string GetMeshPath() const;
            void LoadMeshFromPath(const std::string &path);

            void SetColor(const Color &color);
            Color GetColor() const;

            void SetHasTransparency(const bool &bHasTransparency);
            bool GetHasTransparency() const;

            virtual void ImGuiRender() override;

            virtual nlohmann::json ToJson() const override;
            virtual void FromJson(const nlohmann::json &json) override;

            virtual Component *Clone(GameObject *gameObject) override;
        protected:
        private:
            Model _model = {0};
            std::string _meshPath;
            
            Texture2D _texture = {0};
            std::string _texturePath;

            Color _color = WHITE;

            bool _bHasTransparency = false;
    };
}

#endif /* !MESHRENDERER_HPP_ */
