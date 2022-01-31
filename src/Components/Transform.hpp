/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** Transform
*/

#ifndef TRANSFORM_HPP_
#define TRANSFORM_HPP_

#include "../include.hpp"
#include "../Ecs/Component.hpp"

namespace Components {
    class Transform : public Component {
        public:
            Transform(GameObject *gameObject);
            ~Transform();

            void Translate(Vector3 vec);
            void Rotate(Vector3 vec);

            Vector3 GetPosition() const;
            void SetPosition(Vector3 pos);
            void SetPosition(float x, float y, float z);
            Vector3 GetRotation() const;
            void SetRotation(Vector3 rotation);
            void SetRotation(float x, float y, float z);
            Vector3 GetScale() const;
            void SetScale(Vector3 scale);
            void SetScale(float x, float y, float z);
        protected:
        private:
            Vector3 _position;
            Vector3 _rotation;
            Vector3 _scale;
    };
}

#endif /* !TRANSFORM_HPP_ */
