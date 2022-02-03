/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** UIElement
*/

#ifndef UIELEMENT_HPP_
#define UIELEMENT_HPP_

#include "../../include.hpp"

namespace hr {
    class UIElement {
        public:
            // UIElement();
            // ~UIElement();

            static void CheckBox(const std::string &label, bool (*getter)(void), void (*setter)(bool));

            // static bool FloatN(const char* fieldName, float* value, uint32_t count = 1, float speed = 1.0, float min = 0.0, float max = 0.0, const char* format = "%.3f");
            static void FloatField(const std::string &label, float (*getter)(void), void (*setter)(float), float speed = 1.0, float min = 0.0, float max = 0.0, const char* format = "%.3f");
            static void Vector2Field(const std::string &label, Vector2 (*getter)(void), void (*setter)(Vector2), float speed = 1.0, float min = 0.0, float max = 0.0, const char* format = "%.3f");
            static void Vector3Field(const std::string &label, std::function<Vector3()> getter, std::function<void(Vector3)> setter, float speed = 1.0, float min = 0.0, float max = 0.0, const char* format = "%.3f");
            static void ColorField(const std::string &label, Color (*getter)(void), void (*setter)(Color));

        protected:
        private:
    };
}

#endif /* !UIELEMENT_HPP_ */
