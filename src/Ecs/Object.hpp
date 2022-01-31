/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** Object
*/

#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#pragma once
#include "../include.hpp"

class Object {
    public:
        Object();
        ~Object();

        virtual void Start() = 0;
	    virtual void Update() = 0;
	    virtual void LateUpdate() = 0;
	    virtual void End() = 0;
        
        std::string GetName() const;
        void SetName(const std::string &name);
        bool IsActive() const;
	    void SetActive(bool);
    
    protected:
        std::string _name = "";
        bool _active = true;
    private:
};

#endif /* !OBJECT_HPP_ */
