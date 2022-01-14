/*
** EPITECH PROJECT, 2021
** 3D
** File description:
** Transform
*/

#ifndef TRANSFORM_HPP_
#define TRANSFORM_HPP_

#pragma once
#include "../include.hpp"

namespace IS {
    class Transform {
        public:
            Transform(Vector3 position, Vector3 rotation, float scale);
            ~Transform();

            void increasePosition(Vector3 vec);
            void increaseRotation(Vector3 vec);

            Vector3 getPosition() const;
            Vector3 getRotation() const;
            float getScale() const;

            void setPosition(Vector3 position);
            void setRotation(Vector3 rotation);
            void setScale(float scale);

        private:
            Vector3 _position;
            Vector3 _rotation;
            float _scale;
    };
}

#endif /* !TRANSFORM_HPP_ */
