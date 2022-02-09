/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** MainCamera3D
*/

#ifndef MAINCAMERA3D_HPP_
#define MAINCAMERA3D_HPP_

#include "include.hpp"
#include "../Ecs/Component.hpp"
#include "json.hpp"

namespace hr {
    class MainCamera3D : public Component {
        public:
            MainCamera3D(GameObject *gameObject);
            ~MainCamera3D();

            virtual void Update() override;

            void UpdateCameraMovement();

            Camera3D GetCamera3D() const;

            virtual nlohmann::json ToJson() const override;
            virtual void FromJson(const nlohmann::json &json) override;
        protected:
        private:
            Camera3D _camera;
            float _speed = 20;
            float _turnSpeed = 40;
    };
}

#endif /* !MAINCAMERA3D_HPP_ */
