/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** LightShader
*/

#ifndef LIGHTSHADER_HPP_
#define LIGHTSHADER_HPP_

#include "include.hpp"
#include "DefaultShader.hpp"

namespace hr {
    class Light;
    class GameObject;

    enum LightLoc {
        LOC_ENABLED = 0,
        LOC_TYPE,
        LOC_TARGET,
        LOC_POS,
        LOC_RANGE,
        LOC_COLOR,
        LOC_INTENSITY,
        LOC_COUNT
    };

    class LightShader : public DefaultShader {
        public:
            LightShader();
            ~LightShader();

            void UpdateCameraLoc(Camera3D camera);
            void UpdateLightLoc(Light *light, int id);
            void UpdateLightsLoc(std::vector<GameObject *> lights);

            std::vector<int> GetLocations(int id) const;
        protected:
        private:
            std::vector<std::vector<int>> _locations;
    };
}

#endif /* !LIGHTSHADER_HPP_ */
