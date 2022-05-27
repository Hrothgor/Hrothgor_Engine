/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** RigidBody
*/

#ifndef RIGIDBODY_HPP_
#define RIGIDBODY_HPP_

#include "Include.hpp"
#include "Ecs/Component.hpp"
#include "Json.hpp"

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
            float GetInvMass() const;
            Matrix GetInvTensor() const;
            void SetMass(float mass);

            Vector3 GetForce() const;
            void SetForce(Vector3 force);
            void AddForce(Vector3 force);

            Vector3 GetVelocity() const;
            void SetVelocity(Vector3 velocity);
            void AddVelocity(Vector3 velocity);

            Vector3 GetAngularVelocity() const;
            void SetAngularVelocity(Vector3 angularVelocity);
            void AddAngularVelocity(Vector3 angularVelocity);

            bool GetUseGravity() const;
            void SetUseGravity(bool useGravity);
            bool GetIsDynamic() const;
            void SetIsDynamic(bool isDynamic);

            float GetStaticFriction() const;
            void SetStaticFriction(float staticFriction);
            float GetDynamicFriction() const;
            void SetDynamicFriction(float dynamicFriction);

            void ImGuiRender();
            void OnDrawGizmos() {};

            virtual nlohmann::json ToJson() const override;
            virtual void FromJson(const nlohmann::json &json) override;

            virtual Component *Clone(GameObject *gameObject) override;
        protected:
        private:
            Vector3 _velocity;
            Vector3 _angularVelocity;
            Vector3 _force;

            float _mass = 1;
            bool _useGravity = true;
            bool _isDynamic = true;

            float _staticFriction = 0.5;
            float _dynamicFriction = 0.3;
    };
}

#endif /* !RIGIDBODY_HPP_ */