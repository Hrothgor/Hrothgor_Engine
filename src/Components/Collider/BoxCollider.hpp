/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** BoxCollider
*/

#ifndef BOXCOLLIDER_HPP_
#define BOXCOLLIDER_HPP_

#include "include.hpp"
#include "../../Ecs/Component.hpp"
#include "json.hpp"
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

            Vector3 GetCubeSize() const;
            float GetCubeWidth() const;
            void SetCubeWidth(float width);
            float GetCubeHeight() const;
            void SetCubeHeight(float height);
            float GetCubeLength() const;
            void SetCubeLength(float length);

            void ImGuiRender();
            void OnDrawGizmos();

            virtual nlohmann::json ToJson() const override;
            virtual void FromJson(const nlohmann::json &json) override;

            virtual Component *Clone(GameObject *gameObject) override;
        protected:
        private:
            Vector3 _offset = {0};
            float _cubeWidth = 1;
            float _cubeHeight = 1;
            float _cubeLength = 1;
    };
}

#endif /* !BOXCOLLIDER_HPP_ */