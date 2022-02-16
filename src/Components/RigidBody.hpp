/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** RigidBody
*/

#ifndef RIGIDBODY_HPP_
#define RIGIDBODY_HPP_

#include "include.hpp"
#include "../Ecs/Component.hpp"
#include "json.hpp"

namespace hr {
    class RigidBody : public Component {
        public:
            RigidBody(GameObject *gameObject);
            ~RigidBody();

            void Start() override {};
            void Update() override {};
            void LateUpdate() override {};
            void UpdateOnSimulation() override;
            void End() override {};

            float GetMass() const;
            void SetMass(float mass);
            bool GetUseGravity() const;
            void SetUseGravity(bool useGravity);

            Vector3 GetForce() const;
            void SetForce(Vector3 force);
            void AddForce(Vector3 force);

            Vector3 GetVelocity() const;
            void SetVelocity(Vector3 velocity);
            void AddVelocity(Vector3 velocity);

            void ImGuiRender();
            void OnDrawGizmos() {};

            virtual nlohmann::json ToJson() const override;
            virtual void FromJson(const nlohmann::json &json) override;

            virtual Component *Clone(GameObject *gameObject) override;
        protected:
        private:
            Vector3 _velocity;
            Vector3 _force;

            float _mass = 1;
            bool _useGravity = true;
    };
}

#endif /* !RIGIDBODY_HPP_ */