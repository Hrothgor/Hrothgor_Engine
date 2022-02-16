/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** Template
*/

#include "Template.hpp"

namespace hr {
    Template::Template(GameObject *gameObject)
        : Component(gameObject)
    {
        _name = "Template";
    }

    Template::~Template()
    {
    }

    nlohmann::json Template::ToJson() const
    {
        nlohmann::json json;

        return json;
    }

    void Template::FromJson(const nlohmann::json &json)
    {
        (void)json;
    }

    Component *Template::Clone(GameObject *gameObject)
    {
        Template *ret = new Template(gameObject);
        return ret;
    }
}