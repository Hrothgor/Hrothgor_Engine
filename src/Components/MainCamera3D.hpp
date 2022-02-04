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

namespace hr {
    class MainCamera3D : public Component {
        public:
            MainCamera3D(GameObject *gameObject);
            ~MainCamera3D();

            virtual void Update() override;

            Camera3D GetCamera3D() const;
        protected:
        private:
            Camera3D _camera;
    };
}

#endif /* !MAINCAMERA3D_HPP_ */
