/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** PrimitiveCollider
*/

#ifndef PRIMITIVECOLLIDER_HPP_
#define PRIMITIVECOLLIDER_HPP_

#include "include.hpp"
#include "../Ecs/Component.hpp"
#include "json.hpp"
#include "MeshFilter.hpp"

namespace hr {
    class PrimitiveCollider : public Component {
        public:
            PrimitiveCollider(GameObject *gameObject);
            ~PrimitiveCollider();

            void Start() override {};
            void Update() override {};
            void LateUpdate() override {};
            void End() override {};

            Mesh GetMesh() const;
            void SetMesh(PrimitiveMeshType type);

            PrimitiveMeshType GetType() const;

            float GetCubeWidth() const;
            void SetCubeWidth(float width);
            float GetCubeHeight() const;
            void SetCubeHeight(float height);
            float GetCubeLength() const;
            void SetCubeLength(float length);

            float GetSphereRadius() const;
            void SetSphereRadius(float radius);

            void ImGuiRender();
            void OnDrawGizmos();

            virtual nlohmann::json ToJson() const override;
            virtual void FromJson(const nlohmann::json &json) override;
        protected:
        private:
            PrimitiveMeshType _type;

            Mesh _mesh = {0};

            // for Cube
            float _cubeWidth = 1;
            float _cubeHeight = 1;
            float _cubeLength = 1;
            // for sphere
            float _sphereRadius = 1;
    };
}

#endif /* !PRIMITIVECOLLIDER_HPP_ */