/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** Component
*/

#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

#pragma once
#include "../include.hpp"
#include "Object.hpp"

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

    protected:
        GameObject *GetGameObject() const;
        Transform *GetTransform() const;
    private:
        GameObject *_gameObject = nullptr;
        Transform *_transform = nullptr;
};

#endif /* !COMPONENT_HPP_ */
