/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** Template
*/

#ifndef TEMPLATE_HPP_
#define TEMPLATE_HPP_

#include "include.hpp"
#include "../Ecs/Component.hpp"


namespace hr {
    class Template : public Component {
        public:
            Template(GameObject *gameObject);
            ~Template();

            virtual void Update() override;

        protected:
        private:
    };
}

#endif /* !TEMPLATE_HPP_ */