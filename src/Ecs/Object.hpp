/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** Object
*/

#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#pragma once
#include "include.hpp"
#include "uuid_v4.h"

namespace hr {
    class Object {
        public:
            Object();
            ~Object();

            virtual void Start() = 0;
            virtual void Update() = 0;
            virtual void LateUpdate() = 0;
            virtual void OnDrawGizmos() = 0;
            virtual void End() = 0;
            
            std::string GetName() const;
            void SetName(const std::string &name);

            UUIDv4::UUID GetUUID() const;
            void SetUUID(const std::string &str);

            bool IsActive() const;
            void SetActive(bool);
        
        protected:
            std::string _name = "";
            bool _active = true;
            UUIDv4::UUID _uuid;
        private:
    };
}

#endif /* !OBJECT_HPP_ */
