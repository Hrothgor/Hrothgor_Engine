/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** SphereCollider
*/

#ifndef SPHERECOLLIDER_HPP_
#define SPHERECOLLIDER_HPP_

#include "include.hpp"
#include "../../Ecs/Component.hpp"
#include "json.hpp"
#include "Collider.hpp"

namespace hr {
    class SphereCollider : public Component, public Collider {
        public:
            SphereCollider(GameObject *gameObject);
            ~SphereCollider();

            virtual CollisionPoints TestCollision(
                const Transform *transform,
                const Collider *collider,
                const Transform *colliderTransform
            ) const override;

            virtual CollisionPoints TestCollision(
                const Transform *transform,
                const SphereCollider *sphere,
                const Transform *sphereTransform
            ) const override;

            virtual CollisionPoints TestCollision(
                const Transform *transform,
                const BoxCollider *box,
                const Transform *boxTransform
            ) const override;

            void SetOffset(Vector3 offset);
            Vector3 GetOffset() const;
            float GetSphereRadius() const;
            void SetSphereRadius(float radius);

            void ImGuiRender();
            void OnDrawGizmos();

            virtual nlohmann::json ToJson() const override;
            virtual void FromJson(const nlohmann::json &json) override;

            virtual Component *Clone(GameObject *gameObject) override;
        protected:
        private:
            Vector3 _offset = {0};
            float _sphereRadius = 1;

        protected:
        private:
    };
}

#endif /* !SPHERECOLLIDER_HPP_ */