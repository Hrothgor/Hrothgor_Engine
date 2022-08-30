/*
** EPITECH PROJECT, 2022
** Hrothgor_Engine
** File description:
** JsonManager
*/

#ifndef JSONMANAGER_HPP_
#define JSONMANAGER_HPP_

#include "Include.hpp"
#include "Json.hpp"

namespace hr {
    class JsonManager {
        public:
        /// SAVE
            static void SaveVector3(nlohmann::json &json, const std::string &label, const Vector3 &data);
            static void SaveFloat(nlohmann::json &json, const std::string &label, const float &data);
            static void SaveBool(nlohmann::json &json, const std::string &label, const bool &data);
            static void SaveString(nlohmann::json &json, const std::string &label, const std::string &data);
            static void SaveColor(nlohmann::json &json, const std::string &label, const Color &data);
            static void SaveInt(nlohmann::json &json, const std::string &label, const int &data);

        /// LOAD
            static Vector3 LoadVector3(const nlohmann::json &json, const std::string &label);
            static float LoadFloat(const nlohmann::json &json, const std::string &label);
            static bool LoadBool(const nlohmann::json &json, const std::string &label);
            static std::string LoadString(const nlohmann::json &json, const std::string &label);
            static Color LoadColor(const nlohmann::json &json, const std::string &label);
            static int LoadInt(const nlohmann::json &json, const std::string &label);
        protected:
        private:
    };
}

#endif /* !JSONMANAGER_HPP_ */
