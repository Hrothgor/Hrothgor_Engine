/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** Test
*/

#ifndef TEST_HPP_
#define TEST_HPP_

#include "Include.hpp"
#include "Components.hpp"
#include "Json.hpp"

namespace hr {
    class Test : public Component {
        public:
            Test(GameObject *gameObject);
            ~Test();

            void Start() override {};
            void Update() override {};
            void LateUpdate() override {};
            void UpdateOnSimulation() override;
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

#endif /* !TEST_HPP_ */