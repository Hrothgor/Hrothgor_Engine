/*
** EPITECH PROJECT, 2022
** Hrothgor_Engine
** File description:
** json
*/

#ifndef JSON_INCLUDE_HPP_
#define JSON_INCLUDE_HPP_

#include "Externals/nlohmann/json.hpp"


namespace hr {
    using json = nlohmann::basic_json<>;
}

#endif /* !JSON_HPP_ */
