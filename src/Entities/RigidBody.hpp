/*
** EPITECH PROJECT, 2021
** 3D
** File description:
** RigidBody
*/

#pragma once
#ifndef RIGIDBODY_HPP_
#define RIGIDBODY_HPP_

#include "../include.hpp"

namespace IS {
    class RigidBody {
        public:
            RigidBody();
            ~RigidBody();

            Vector3 getVelocity() const;
            void setVelocity(Vector3 velocity);
            void setVelocity(float x, float y, float z);
            Vector3 getForce() const;
            void setForce(Vector3 force);
            void setForce(float x, float y, float z);
            float getMass() const;
            void setMass(float mass);

        protected:
        private:
            Vector3 _velocity;
            Vector3 _force;
            float _mass;
    };
}

#endif /* !RIGIDBODY_HPP_ */
