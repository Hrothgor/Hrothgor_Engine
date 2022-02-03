/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** MeshRenderer
*/

#ifndef MESHRENDERER_HPP_
#define MESHRENDERER_HPP_

#include "../include.hpp"
#include "../Ecs/Component.hpp"

namespace hr {
    class MeshRenderer : public Component {
        public:
            MeshRenderer(GameObject *gameObject);
            ~MeshRenderer();

            virtual void Update() override;

            void Load(const std::string &path, const std::string &texturePath = "");

            void LoadModelFromPath(const std::string &path);
            void LoadTextureFromPath(const std::string &path);

            Model GetModel() const;
            Texture2D GetTexture() const;

            std::string GetModelPath() const;
            std::string GetTexturePath() const;

            virtual void ImGuiRender() override;
        protected:
        private:
            Model _model = {};
            Texture2D _texture = {0};

            std::string _modelPath;
            std::string _texturePath;
    };
}

#endif /* !MESHRENDERER_HPP_ */
