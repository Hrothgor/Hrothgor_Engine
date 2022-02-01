/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** Light
*/

#ifndef LIGHT_HPP_
#define LIGHT_HPP_

#include "../include.hpp"
#include "../Ecs/Component.hpp"


namespace hr {
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

    enum LightType {
        DIRECTIONAL,
        POINT,
    };

    class Light : public Component {
        public:
            Light(GameObject *gameObject);
            ~Light();

            virtual void Update() override;

            void UpdateValues(Shader shader);

            LightType GetType() const;
            void SetType(const LightType &type);

            Vector3 GetTarget() const;
            void SetTarget(const Vector3 &target);
            
            float GetRange() const;
            void SetRange(const float &range);
            
            float GetIntensity() const;
            void SetIntensity(const float &intensity);

            Color GetColor() const;
            void SetColor(const Color &color);
        protected:
        private:
            LightType _type;
            Vector3 _target;
            float _range;
            Color _color;
            float _intensity;

            std::vector<int> _locations;
    };
}

#endif /* !LIGHT_HPP_ */