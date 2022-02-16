/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** MeshFilter
*/

#ifndef MESHFILTER_HPP_
#define MESHFILTER_HPP_

#include "include.hpp"
#include "../Ecs/Component.hpp"
#include "json.hpp"

namespace hr {
    enum PrimitiveMeshType {
        CUBE = 0,
        SPHERE,
        PLANE,
        MESH,
    };

    class MeshFilter : public Component {
        public:
            MeshFilter(GameObject *gameObject);
            ~MeshFilter();

            void Start() override {};
            void Update() override;
            void LateUpdate() override {};
            void End() override {};

            Model GetModel() const;
            void SetModel(PrimitiveMeshType type);

            PrimitiveMeshType GetType() const;

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

            std::string GetMeshPath() const;
            void LoadMeshFromPath(const std::string &path);

            void ImGuiRender();
            void OnDrawGizmos() {};

            virtual nlohmann::json ToJson() const override;
            virtual void FromJson(const nlohmann::json &json) override;

            virtual Component *Clone(GameObject *gameObject) override;
        protected:
        private:
            PrimitiveMeshType _type;

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
            // for mesh
            std::string _meshPath;
    };
}

#endif /*  MESHFILTER_HPP_ */