/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** PrimitiveRenderer
*/

#ifndef PRIMITIVERENDERER_HPP_
#define PRIMITIVERENDERER_HPP_

#include "include.hpp"
#include "../Ecs/Component.hpp"
#include "json.hpp"

namespace hr {
    enum PrimitiveMesh {
        CUBE = 0,
        SPHERE,
        PLANE,
    };

    class PrimitiveRenderer : public Component {
        public:
            PrimitiveRenderer(GameObject *gameObject);
            ~PrimitiveRenderer();

            void Start() override {};
            void Update() override;
            void LateUpdate() override {};
            void End() override {};

            Model GetModel() const;
            void SetModel(PrimitiveMesh mesh);

            PrimitiveMesh GetType() const;

            float GetCubeWidth() const;
            void SetCubeWidth(float width);
            float GetCubeHeight() const;
            void SetCubeHeight(float height);
            float GetCubeLength() const;
            void SetCubeLength(float length);

            float GetSphereRadius() const;
            void SetSphereRadius(float radius);
            int GetSphereRings() const;
            void SetSphereRings(int rings);
            int GetSphereSlices() const;
            void SetSphereSlices(int slices);

            float GetPlaneWidth() const;
            void SetPlaneWidth(float width);
            float GetPlaneLength() const;
            void SetPlaneLength(float length);
            int GetPlaneResolution() const;
            void SetPlaneResolution(int resolution);

            void ImGuiRender();
            void OnDrawGizmos() {};

            virtual nlohmann::json ToJson() const override;
            virtual void FromJson(const nlohmann::json &json) override;
        protected:
        private:
            PrimitiveMesh _type;

            Model _model = {0};

            // for Cube
            float _cubeWidth = 1;
            float _cubeHeight = 1;
            float _cubeLength = 1;
            // for sphere
            float _sphereRadius = 1;
            int _sphereRings = 8;
            int _sphereSlices = 8;
            // for plane
            float _planeWidth = 1;
            float _planeLength = 1;
            int _planeResolution = 5;
    };
}

#endif /*  PRIMITIVERENDERER_HPP_ */