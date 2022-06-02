/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** String
*/

#ifndef STRING_HPP_
#define STRING_HPP_

#include "Include.hpp"

namespace hr {
    class String {
        public:
            static bool EndWith(std::string const &value, std::string const &ending);
            static std::string NameByPath(std::string const &path);
        protected:
        private:
    };
}

#endif /* !STRING_HPP_ */
