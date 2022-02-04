/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** Light
*/

#ifndef LIGHT_HPP_
#define LIGHT_HPP_

#include "include.hpp"
#include "../Ecs/Component.hpp"

namespace hr {
    enum LightType {
        DIRECTIONAL,
        POINT,
    };

    class Light : public Component {
        public:
            Light(GameObject *gameObject);
            ~Light();

            virtual void Update() override;

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

            virtual void ImGuiRender() override;
            virtual void OnDrawGizmos() override;
        protected:
        private:
            LightType _type;
            Vector3 _target;
            Vector3 _front;
            float _range;
            Color _color;
            float _intensity;
    };
}

#endif /* !LIGHT_HPP_ */