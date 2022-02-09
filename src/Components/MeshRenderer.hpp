/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** MeshRenderer
*/

#ifndef MESHRENDERER_HPP_
#define MESHRENDERER_HPP_

#include "include.hpp"
#include "../Ecs/Component.hpp"
#include "json.hpp"

namespace hr {
    class MeshRenderer : public Component {
        public:
            MeshRenderer(GameObject *gameObject);
            ~MeshRenderer();

            virtual void Update() override;

            void LoadModelFromPath(const std::string &path);
            void LoadTextureFromPath(const std::string &path);

            Texture2D GetTexture() const;

            std::string GetTexturePath() const;

            virtual void ImGuiRender() override;

            virtual nlohmann::json ToJson() const override;
            virtual void FromJson(const nlohmann::json &json) override;
        protected:
        private:
            Texture2D _texture = {0};

            std::string _texturePath;
    };
}

#endif /* !MESHRENDERER_HPP_ */
