/*
** EPITECH PROJECT, 2022
** Hrothgor_Engine
** File description:
** LightShader
*/

#include "LightShader.hpp"
#include "Components/Light.hpp"
#include "Components/Transform.hpp"
#include "Ecs/GameObject.hpp"

namespace hr {
    LightShader::LightShader()
        : DefaultShader("Engine/Ressources/Shaders/Light.vs", "Engine/Ressources/Shaders/Light.fs")
        , _locationsLights(MAX_LIGHTS)
    {
        for (int i = 0; i < MAX_LIGHTS; i++)
            _locationsLights[i] = GetLocationsLight(i);

        _locationNbLights = GetShaderLocation(_shader, "nbLights");
        _locationLightSpaceMatrix = GetShaderLocation(_shader, "lightSpaceMatrix");
        _locationShadowMap = GetShaderLocation(_shader, "shadowMap");
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
        int type = light->GetType();
        SetShaderValue(_shader, _locationsLights[id][LOC_TYPE], &type, SHADER_UNIFORM_INT);

        float target[3] = {light->GetTarget().x, light->GetTarget().y, light->GetTarget().z};
        SetShaderValue(_shader, _locationsLights[id][LOC_TARGET], &target, SHADER_UNIFORM_VEC3);

        Transform *transform = light->GetTransform();
        float pos[3] = {transform->GetPositionWorld().x,
                        transform->GetPositionWorld().y,
                        transform->GetPositionWorld().z};
        SetShaderValue(_shader, _locationsLights[id][LOC_POS], &pos, SHADER_UNIFORM_VEC3);

        float range = light->GetRange();
        SetShaderValue(_shader, _locationsLights[id][LOC_RANGE], &range, SHADER_UNIFORM_FLOAT);

        Vector4 vec = ColorNormalize(light->GetColor());
        float color[4] = {vec.x, vec.y, vec.z, vec.w};
        SetShaderValue(_shader, _locationsLights[id][LOC_COLOR], &color, SHADER_UNIFORM_VEC4);

        float intensity = light->GetIntensity();
        SetShaderValue(_shader, _locationsLights[id][LOC_INTENSITY], &intensity, SHADER_UNIFORM_FLOAT);
    }

    void LightShader::UpdateLightsLoc(std::vector<GameObject *> lights)
    {
        int nbLights = MAX_LIGHTS;
        for (unsigned int i = 0; i < MAX_LIGHTS; i++) {
            if (i < lights.size()) {
                UpdateLightLoc(lights[i]->GetComponent<Light>(), i);
            } else {
                nbLights = i;
                break;
            }
        }
        SetShaderValue(_shader, _locationNbLights, &nbLights, SHADER_UNIFORM_INT);
    }

    void LightShader::UpdateLightSpaceMatrix(Matrix mat)
    {
        SetShaderValueMatrix(_shader, _locationLightSpaceMatrix, mat);
    }

    void LightShader::UpdateShadowMap(Texture texture)
    {
        SetShaderValueTexture(_shader, _locationShadowMap, texture);
    }

    std::vector<int> LightShader::GetLocationsLight(int id) const
    {
        std::vector<int> locations(LOC_LIGHT_SHADER_COUNT, 0);

        locations[LOC_TYPE] = GetShaderLocation(_shader, ("lights[" + std::to_string(id) + "].type").c_str());
        locations[LOC_TARGET] = GetShaderLocation(_shader, ("lights[" + std::to_string(id) + "].target").c_str());
        locations[LOC_POS] = GetShaderLocation(_shader, ("lights[" + std::to_string(id) + "].position").c_str());
        locations[LOC_RANGE] = GetShaderLocation(_shader, ("lights[" + std::to_string(id) + "].range").c_str());
        locations[LOC_COLOR] = GetShaderLocation(_shader, ("lights[" + std::to_string(id) + "].color").c_str());
        locations[LOC_INTENSITY] = GetShaderLocation(_shader, ("lights[" + std::to_string(id) + "].intensity").c_str());

        return locations;
    }
}