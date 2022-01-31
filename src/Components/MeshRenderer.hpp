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

namespace Components {
    class MeshRenderer : public Component {
        public:
            MeshRenderer(GameObject *gameObject);
            ~MeshRenderer();

            virtual void Update() override;

            void Load(const std::string &path, const std::string &texturePath = "");

            Model GetModel() const;
            Texture2D GetTexture() const;
        protected:
        private:
            Model _model;
            Texture2D _texture = {0};
    };
}

#endif /* !MESHRENDERER_HPP_ */
