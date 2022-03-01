/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** AssetsManager
*/

#ifndef ASSETSMANAGER_HPP_
#define ASSETSMANAGER_HPP_

#include "include.hpp"

namespace hr {
    class AssetsManager {
        public:
            AssetsManager();
            ~AssetsManager();

            void Start();

            // std::map<std::string, Texture> GetTextures() const;
            // std::map<std::string, Model> GetModels() const;
            bool TextureContains(const std::string &key) const;
            bool ModelContains(const std::string &key) const;
            Texture2D GetTexture(const std::string &key);
            Texture2D *GetTextureAddr(const std::string &key);
            Model GetModel(const std::string &key);

        protected:
        private:
            std::map<std::string, Texture2D> _textures;
            std::map<std::string, Model> _models;

        protected:
            static AssetsManager *instance;
        public:
            AssetsManager(AssetsManager &other) = delete;
            void operator=(const AssetsManager &) = delete;
            static AssetsManager *Get() {
                if (instance == nullptr)
                    instance = new AssetsManager();
                return instance;
            };
    };
}

#endif /* !ASSETSMANAGER_HPP_ */
