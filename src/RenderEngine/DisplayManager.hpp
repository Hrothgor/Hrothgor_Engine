/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** DisplayManager
*/

#ifndef DISPLAYMANAGER_HPP_
#define DISPLAYMANAGER_HPP_

#include "Include.hpp"
#include "UI/ImGuiLayer.hpp"

namespace hr {
    class DisplayManager {
        public:
            DisplayManager();
            ~DisplayManager();

            void Start();
            void End();

            void Clear(Color color);
            void Draw();

            RenderTexture GetRenderTexture() const;
            Texture *GetFrameBufferTexture();

        protected:
        private:
            RenderTexture _renderTexture;

            ImGuiLayer _imGuiLayer;

        protected:
            static DisplayManager *instance;
        public:
            DisplayManager(DisplayManager &other) = delete;
            void operator=(const DisplayManager &) = delete;
            static DisplayManager *Get() {
                if (instance == nullptr)
                    instance = new DisplayManager();
                return instance;
            };
    };
}

#endif /* !DISPLAYMANAGER_HPP_ */
