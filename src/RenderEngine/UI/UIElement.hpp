/*
** EPITECH PROJECT, 2022
** Hrothgor_Engine
** File description:
** UIElement
*/

#ifndef UIELEMENT_HPP_
#define UIELEMENT_HPP_

#include "Include.hpp"

namespace hr {
    class UIElement {
        public:
            static void Header(const std::string &label);

            static void CheckBox(const std::string &label, std::function<bool()> getter, std::function<void(bool)> setter);

            static void SliderFloatField(const std::string &label, std::function<float()> getter, std::function<void(float)> setter, float min = 0.0, float max = 0.0, const char* format = "%.3f", float power = 1.0);

            static void EnumField(const std::string &label, std::function<int()> getter, std::function<void(int)> setter, std::vector<std::string> list);

            // static bool FloatN(const char* fieldName, float* value, uint32_t count = 1, float speed = 1.0, float min = 0.0, float max = 0.0, const char* format = "%.3f");
            static void IntField(const std::string &label, std::function<int()> getter, std::function<void(int)> setter, float speed = 1.0, int min = 0.0, int max = 0.0, const char* format = "%.3f");
            static void FloatField(const std::string &label, std::function<float()> getter, std::function<void(float)> setter, float speed = 1.0, float min = 0.0, float max = 0.0, const char* format = "%.3f");
            static void Vector2Field(const std::string &label, std::function<Vector2()> getter, std::function<void(Vector2)> setter, float speed = 1.0, float min = 0.0, float max = 0.0, const char* format = "%.3f");
            static void Vector3Field(const std::string &label, std::function<Vector3()> getter, std::function<void(Vector3)> setter, float speed = 1.0, float min = 0.0, float max = 0.0, const char* format = "%.3f");
            static void ColorField(const std::string &label, std::function<Color()> getter, std::function<void(Color)> setter);

            static void StringField(const std::string &label, std::function<std::string()> getter, std::function<void(std::string)> setter);

            static void ModelField(const std::string &label, std::function<std::string()> getter, std::function<void(std::string)> setter);
            static void TextureField(const std::string &label, std::function<std::string()> getter, std::function<void(std::string)> setter);
        protected:
        private:
            static void StartField(const std::string &label);
            static void EndField();
    };
}

#endif /* !UIELEMENT_HPP_ */
