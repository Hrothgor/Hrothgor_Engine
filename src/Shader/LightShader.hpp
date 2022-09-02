/*
** EPITECH PROJECT, 2022
** Hrothgor_Engine
** File description:
** LightShader
*/

#ifndef LIGHTSHADER_HPP_
#define LIGHTSHADER_HPP_

#include "Include.hpp"
#include "DefaultShader.hpp"

namespace hr {
    class Light;
    class GameObject;

    enum LightShaderLoc {
        LOC_TYPE = 0,
        LOC_TARGET,
        LOC_POS,
        LOC_RANGE,
        LOC_COLOR,
        LOC_INTENSITY,
        LOC_LIGHT_SHADER_COUNT
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
            int _locationNbLights;
    };
}

#endif /* !LIGHTSHADER_HPP_ */
