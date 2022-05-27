/*
** EPITECH PROJECT, 2022
** Physics_engine
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

        std::cout << Engine::Get()->GetMainCamera()->GetTransform()->GetPositionWorld().x << std::endl;
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
        Test *ret = new Test(gameObject);
        return ret;
    }

    extern "C" Component *entryPoint()
    {
        return new Test(nullptr);
    }
}