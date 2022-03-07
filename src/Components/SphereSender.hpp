/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** SphereSender
*/

#ifndef SPHERESENDER_HPP_
#define SPHERESENDER_HPP_

#include "include.hpp"
#include "../Ecs/Component.hpp"
#include "json.hpp"

namespace hr {
    class SphereSender : public Component {
        public:
            SphereSender(GameObject *gameObject);
            ~SphereSender();

            void UpdateOnSimulation() override;

            void ImGuiRender() {};
            void OnDrawGizmos() {};

            virtual nlohmann::json ToJson() const override;
            virtual void FromJson(const nlohmann::json &json) override;

            virtual Component *Clone(GameObject *gameObject) override;
        protected:
        private:
    };
}

#endif /* !SPHERESENDER_HPP_ */