/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** MainCamera3D
*/

#ifndef MAINCAMERA3D_HPP_
#define MAINCAMERA3D_HPP_

#include "Include.hpp"
#include "Ecs/Component.hpp"
#include "Json.hpp"

namespace hr {
    class MainCamera3D : public Component {
        public:
            MainCamera3D(GameObject *gameObject);
            ~MainCamera3D();

            virtual void Update() override;

            void UpdateCameraMovement();

            Camera3D GetCamera3D() const;

            void SetCamera3D(const Camera3D &camera3D);
            void SetSpeed(float speed);
            void SetTurnSpeed(float turnSpeed);

            virtual nlohmann::json ToJson() const override;
            virtual void FromJson(const nlohmann::json &json) override;

            virtual Component *Clone(GameObject *gameObject) override;
        protected:
        private:
            Camera3D _camera;
            float _speed = 40;
            float _turnSpeed = 40;
    };
}

#endif /* !MAINCAMERA3D_HPP_ */
