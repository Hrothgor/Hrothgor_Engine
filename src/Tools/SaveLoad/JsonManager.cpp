/*
** EPITECH PROJECT, 2022
** Hrothgor_Engine
** File description:
** JsonManager
*/

#include "JsonManager.hpp"

namespace hr {

    /// SAVE

    void JsonManager::SaveVector3(nlohmann::json &json, const std::string &label, const Vector3 &data)
    {
        json[label] = {data.x, data.y, data.z};
    }

    void JsonManager::SaveFloat(nlohmann::json &json, const std::string &label, const float &data)
    {
        json[label] = data;
    }

    void JsonManager::SaveBool(nlohmann::json &json, const std::string &label, const bool &data)
    {
        json[label] = data;
    }

    void JsonManager::SaveString(nlohmann::json &json, const std::string &label, const std::string &data)
    {
        json[label] = data;
    }

    void JsonManager::SaveColor(nlohmann::json &json, const std::string &label, const Color &data)
    {
        json[label] = {data.r, data.g, data.b, data.a};
    }

    void JsonManager::SaveInt(nlohmann::json &json, const std::string &label, const int &data)
    {
        json[label] = data;
    }

    /// LOAD

    Vector3 JsonManager::LoadVector3(const nlohmann::json &json, const std::string &label)
    {
        try
        {
            Vector3 ret = {json.at(label).at(0).get<float>(), json.at(label).at(1).get<float>(), json.at(label).at(2).get<float>()};
            return ret;
        }
        catch (json::exception &ex)
        {
            std::cerr << ex.what() << std::endl;
            return {0, 0, 0};
        }
    }

    float JsonManager::LoadFloat(const nlohmann::json &json, const std::string &label)
    {
        try
        {
            float ret = json.at(label).get<float>();
            return ret;
        }
        catch (json::exception &ex)
        {
            std::cerr << ex.what() << std::endl;
            return 0;
        }
    }

    bool JsonManager::LoadBool(const nlohmann::json &json, const std::string &label)
    {
        try
        {
            bool ret = json.at(label).get<bool>();
            return ret;
        }
        catch (json::exception &ex)
        {
            std::cerr << ex.what() << std::endl;
            return false;
        }
    }

    std::string JsonManager::LoadString(const nlohmann::json &json, const std::string &label)
    {
        try
        {
            std::string ret = json.at(label).get<std::string>();
            return ret;
        }
        catch (json::exception &ex)
        {
            std::cerr << ex.what() << std::endl;
            return "";
        }
    }

    Color JsonManager::LoadColor(const nlohmann::json &json, const std::string &label)
    {
        try
        {
            Color ret = {json.at(label).at(0).get<unsigned char>(), json.at(label).at(1).get<unsigned char>(), json.at(label).at(2).get<unsigned char>(), json.at(label).at(3).get<unsigned char>()};
            return ret;
        }
        catch (json::exception &ex)
        {
            std::cerr << ex.what() << std::endl;
            std::cout << "expection json" << std::endl;
            return WHITE;
        }
    }

    int JsonManager::LoadInt(const nlohmann::json &json, const std::string &label)
    {
        try
        {
            int ret = json.at(label).get<int>();
            return ret;
        }
        catch (json::exception &ex)
        {
            std::cerr << ex.what() << std::endl;
            return 0;
        }
    }
}