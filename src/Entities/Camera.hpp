/*
** EPITECH PROJECT, 2021
** 3D
** File description:
** Camera
*/

#pragma once
#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include "../global.hpp"

namespace IS {

    struct CameraAnimation {
        bool isRunning;
        Vector3 begin;
        Vector3 end;
        float length;
    };

    class Camera {
        public:
            Camera();
            ~Camera();

            void update();
            void startAnimation(Vector3 begin, Vector3 end, Vector3 target, float length);

            Camera3D getCamera3D() const;
            Vector3 getPosition() const;
            Vector3 getTarget() const;

        protected:
        private:
            Camera3D _camera;
            CameraAnimation _currentAnimation = { 0 };
    };
}

#endif /* !CAMERA_HPP_ */
