/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** Component
*/

#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

#pragma once
#include "include.hpp"
#include "Object.hpp"
#include "json.hpp"

namespace hr {
    class Transform;
    class GameObject;

    class Component : public Object {
        public:
            Component(GameObject *gameObject);
            ~Component();

            virtual void Start() override {};
            virtual void Update() override {};
            virtual void LateUpdate() override {};
            virtual void End() override {};

            virtual void ImGuiRender() {};
            virtual void OnDrawGizmos() {};

            virtual nlohmann::json ToJson() const = 0;
            virtual void FromJson(const nlohmann::json &json) = 0;

            GameObject *GetGameObject() const;
            Transform *GetTransform() const;
        protected:
        private:
            GameObject *_gameObject = nullptr;
            Transform *_transform = nullptr;
    };
}



#endif /* !COMPONENT_HPP_ */
