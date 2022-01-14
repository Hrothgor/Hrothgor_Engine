/*
** EPITECH PROJECT, 2021
** 3D
** File description:
** Light
*/

#pragma once
#ifndef LIGHTVALUE_HPP_
#define LIGHTVALUE_HPP_

#include "../include.hpp"

namespace IS {
    class LightValue {
        public:
            LightValue(Vector3 position, Color color);
            ~LightValue();

            Vector3 getPosition() const;
            Color getColor() const;
            void setPosition(Vector3 position);
            void setColor(Color color);

        protected:
        private:
            Vector3 _position;
            Color _color;
    };
}

#endif /* !LIGHTVALUE_HPP_ */
