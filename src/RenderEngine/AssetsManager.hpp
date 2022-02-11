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

        protected:
        private:
            std::unordered_map<std::string, Texture> _textures;
            std::unordered_map<std::string, Model> _models;

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
