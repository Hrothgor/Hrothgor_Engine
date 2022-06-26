/*
** EPITECH PROJECT, 2022
** Hrothgor_Engine
** File description:
** Test
*/

#include "Test.hpp"
#include "Engine.hpp"

namespace hr {
    Test::Test(GameObject *gameObject)
        : Component(gameObject)
    {
        _name = "Test";
    }

    Test::~Test()
    {
    }

    void Test::UpdateOnSimulation()
    {
        hr::Engine::Get()->SetSimulating(true);
    }

    nlohmann::json Test::ToJson() const
    {
        nlohmann::json json;

        return json;
    }

    void Test::FromJson(const nlohmann::json &json)
    {
        (void)json;
    }

    Component *Test::Clone(GameObject *gameObject)
    {
        Test *ret = new Test(gameObject );
        return ret;
    }

    extern "C" Component *entryPoint()
    {
        return new Test(nullptr);
    }

    extern "C" void linkSingleton(void *test)
    {
        hr::Engine::Set(test);
    }
}