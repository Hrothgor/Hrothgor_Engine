/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** BoxCollider
*/

#ifndef BOXCOLLIDER_HPP_
#define BOXCOLLIDER_HPP_

#include "Include.hpp"
#include "Ecs/Component.hpp"
#include "Json.hpp"
#include "Collider.hpp"

namespace hr {
    class BoxCollider : public Component, public Collider {
        public:
            BoxCollider(GameObject *gameObject);
            ~BoxCollider();

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

            Vector3 GetSize() const;
            float GetWidth() const;
            void SetWidth(float width);
            float GetHeight() const;
            void SetHeight(float height);
            float GetLength() const;
            void SetLength(float length);

            void ImGuiRender();
            void OnDrawGizmos();

            virtual nlohmann::json ToJson() const override;
            virtual void FromJson(const nlohmann::json &json) override;

            virtual Component *Clone(GameObject *gameObject) override;
        protected:
        private:
            Vector3 _offset = {0};
            float _width = 1;
            float _height = 1;
            float _length = 1;
    };
}

#endif /* !BOXCOLLIDER_HPP_ */