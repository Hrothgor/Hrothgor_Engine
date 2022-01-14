/*
** EPITECH PROJECT, 2021
** 1
** File description:
** TexturedModel
*/

#pragma once
#ifndef TEXTUREDMODEL_HPP_
#define TEXTUREDMODEL_HPP_

#include "../include.hpp"

namespace IS {
    class TexturedModel {
        public:
            TexturedModel() {};
            TexturedModel(const std::string &modelPath);
            TexturedModel(const std::string &modelPath, const std::string &texturePath);
            TexturedModel(Mesh mesh, const std::string &texturePath);
            TexturedModel(Mesh mesh);
            TexturedModel(Model model);
            ~TexturedModel();

            void resetFrame();
            void nextFrame();
            void prevFrame();

            void clean();

            void setShader(Shader shader);
            void setColor(Color color, int materialNumber);
            bool hasShader();

            Model getModel() const;
            Texture2D getTexture() const;
            void setModel(Model model);
            void setTransform(Matrix matrix);

        protected:
        private:
            std::vector<Model> _models;
            Texture2D _texture = {0};
            int _currentFrame = 0;
            int _nbFrame = 0;
    };
}

#endif /* !TEXTUREDMODEL_HPP_ */
