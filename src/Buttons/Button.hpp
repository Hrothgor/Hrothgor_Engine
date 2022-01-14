/*
** EPITECH PROJECT, 2021
** B-YEP-400-MPL-4-1-indiestudio-cyril.grosjean
** File description:
** Button
*/

#pragma once
#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include "../global.hpp"
#include "../Entities/Camera.hpp"

namespace IS {
    class Button {
        public:
            Button(std::string texture_path, Vector2 pos, void (IS::Button::*func)(void), int nbFrame = 3);
            ~Button();

            virtual void callFunction();
            void update();

            void increasePosition(Vector2 position);
            void increaseRotation(float rotation);
            void increaseScale(float scale);

            void setPosition(Vector2 position);
            void setRotation(float rotation);
            void setScale(float scale);

            Texture2D getTexture() const;
            Vector2 getPosition() const;
            float getRotation() const;
            float getScale() const;
            Rectangle getRect() const;

            //// BUTTON FUNC ////
            void quitButton();
            /////////////////////

        protected:
            Texture2D _texture;
            Rectangle _rect;
            Vector2 _position;
            float _rotation = 0;
            float _scale = 1;
            int _nbFrame;
        private:
            void (IS::Button::*_func)(void);
    };
}

#endif /* !BUTTON_HPP_ */