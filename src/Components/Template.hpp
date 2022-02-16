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
#include "json.hpp"

namespace hr {
    class Template : public Component {
        public:
            Template(GameObject *gameObject);
            ~Template();

            void Start() override {};
            void Update() override {};
            void LateUpdate() override {};
            void UpdateOnSimulation() override {};
            void End() override {};

            void ImGuiRender() {};
            void OnDrawGizmos() {};

            virtual nlohmann::json ToJson() const override;
            virtual void FromJson(const nlohmann::json &json) override;

            virtual Component *Clone(GameObject *gameObject) override;
        protected:
        private:
    };
}

#endif /* !TEMPLATE_HPP_ */