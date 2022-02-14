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
            void LoadProject(const std::string &path);

            // std::map<std::string, Texture> GetEngineTexture() const;
            // std::map<std::string, Model> GetEngineModel() const;
            bool EngineTextureContains(const std::string &key) const;
            bool EngineModelContains(const std::string &key) const;
            Texture2D EngineTextureGet(const std::string &key);
            Model EngineModelGet(const std::string &key);

            // std::map<std::string, Texture> GetProjectTexture() const;
            // std::map<std::string, Model> GetProjectModel() const;
            bool ProjectTextureContains(const std::string &key) const;
            bool ProjectModelContains(const std::string &key) const;
            Texture2D ProjectTextureGet(const std::string &key);
            Model ProjectModelGet(const std::string &key);

        protected:
        private:
            std::map<std::string, Texture2D> _engineTextures;
            std::map<std::string, Model> _engineModels;

            std::map<std::string, Texture2D> _projectTextures;
            std::map<std::string, Model> _projectModels;          

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
