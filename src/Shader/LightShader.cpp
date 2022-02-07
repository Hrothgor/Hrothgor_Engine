/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** LightShader
*/

#include "LightShader.hpp"
#include "../Components/Light.hpp"
#include "../Components/Transform.hpp"
#include "../Ecs/GameObject.hpp"

namespace hr {
    LightShader::LightShader()
        : DefaultShader("ressources/Shaders/Light.vs", "ressources/Shaders/Light.fs")
        , _locations(MAX_LIGHTS)
    {
        for (int i = 0; i < MAX_LIGHTS; i++)
            _locations[i] = GetLocations(i);

        int ambientLoc = GetShaderLocation(_shader, "ambient");
        float ambientValue[4] =  { 0.1, 0.1, 0.1, 1.0 };
        SetShaderValue(_shader, ambientLoc, &ambientValue, SHADER_UNIFORM_VEC4);
    }

    LightShader::~LightShader()
    {
    }

    void LightShader::UpdateCameraLoc(Camera3D camera)
    {
        float cameraPos[3] = { camera.position.x, camera.position.y, camera.position.z };
        SetShaderValue(_shader, _shader.locs[SHADER_LOC_VECTOR_VIEW], cameraPos, SHADER_UNIFORM_VEC3);
    }

    void LightShader::UpdateLightLoc(Light *light, int id)
    {
        int enabled = 1;
        SetShaderValue(_shader, _locations[id][LOC_ENABLED], &enabled, SHADER_UNIFORM_INT);

        int type = light->GetType();
        SetShaderValue(_shader, _locations[id][LOC_TYPE], &type, SHADER_UNIFORM_INT);

        float target[3] = {light->GetTarget().x, light->GetTarget().y, light->GetTarget().z};
        SetShaderValue(_shader, _locations[id][LOC_TARGET], &target, SHADER_UNIFORM_VEC3);

        Transform *transform = light->GetTransform();
        float pos[3] = {transform->GetPositionWorld().x,
                        transform->GetPositionWorld().y,
                        transform->GetPositionWorld().z};
        SetShaderValue(_shader, _locations[id][LOC_POS], &pos, SHADER_UNIFORM_VEC3);

        float range = light->GetRange();
        SetShaderValue(_shader, _locations[id][LOC_RANGE], &range, SHADER_UNIFORM_FLOAT);

        Vector4 vec = ColorNormalize(light->GetColor());
        float color[4] = {vec.x, vec.y, vec.z, vec.w};
        SetShaderValue(_shader, _locations[id][LOC_COLOR], &color, SHADER_UNIFORM_VEC4);

        float intensity = light->GetIntensity();
        SetShaderValue(_shader, _locations[id][LOC_INTENSITY], &intensity, SHADER_UNIFORM_FLOAT);
    }

    void LightShader::UpdateLightsLoc(std::vector<GameObject *> lights)
    {
        for (unsigned int i = 0; i < MAX_LIGHTS; i++) {
            if (i < lights.size()) {
                UpdateLightLoc(lights[i]->GetComponent<Light>(), i);
            } else {
                int enabled = 0;
                SetShaderValue(_shader, _locations[i][LOC_ENABLED], &enabled, SHADER_UNIFORM_INT);
            }
        }
    }

    std::vector<int> LightShader::GetLocations(int id) const
    {
        std::vector<int> locations(LOC_COUNT, 0);

        locations[LOC_ENABLED] = GetShaderLocation(_shader, ("lights[" + std::to_string(id) + "].enabled").c_str());
        locations[LOC_TYPE] = GetShaderLocation(_shader, ("lights[" + std::to_string(id) + "].type").c_str());
        locations[LOC_TARGET] = GetShaderLocation(_shader, ("lights[" + std::to_string(id) + "].target").c_str());
        locations[LOC_POS] = GetShaderLocation(_shader, ("lights[" + std::to_string(id) + "].position").c_str());
        locations[LOC_RANGE] = GetShaderLocation(_shader, ("lights[" + std::to_string(id) + "].range").c_str());
        locations[LOC_COLOR] = GetShaderLocation(_shader, ("lights[" + std::to_string(id) + "].color").c_str());
        locations[LOC_INTENSITY] = GetShaderLocation(_shader, ("lights[" + std::to_string(id) + "].intensity").c_str());

        return locations;
    }
}