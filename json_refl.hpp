
#pragma once

#include <nlohmann/json.hpp>


struct universal_serializer_msk
{
    template <typename T>
    requires std::is_enum_v<T>
    static void to_json(nlohmann::json &j, const T &value)
    {
        template for (constexpr auto it : std::define_static_array(std::meta::enumerators_of(^^T)))
        {
            if(value & [:it:] ){
                j.push_back(identifier_of(it));
            }
        }
    }

    template <typename T>
    requires std::is_enum_v<T>
    static void from_json(const nlohmann::json &j, T &value)
    {
        constexpr auto ctx = std::meta::access_context::unchecked();

        value = (T)0;

        template for (constexpr auto it : define_static_array(enumerators_of(^^T)))
        {
            for( auto & j_it : j){
                if(j_it == identifier_of(it)){
                    value |= [:it:];
                    break;
                }
            }
        }
    }
};

struct universal_serializer
{
    template <typename T>
    requires std::is_enum_v<T>
    static void to_json(nlohmann::json &j, const T &value)
    {
        template for (constexpr auto it : std::define_static_array(std::meta::enumerators_of(^^T)))
        {
            if(value == [:it:]){
                j = identifier_of(it);
            }
        }
    }

    template <typename T>
    requires std::is_enum_v<T>
    static void from_json(const nlohmann::json &j, T &value)
    {
        constexpr auto ctx = std::meta::access_context::unchecked();

        template for (constexpr auto it : define_static_array(enumerators_of(^^T)))
        {
            if(j == identifier_of(it)){
                value = [:it:];
            }
        }
    }

    template <typename T>
    static void to_json(nlohmann::json &j, const T &value)
    {
        constexpr auto ctx = std::meta::access_context::unchecked();

        template for (constexpr auto it : define_static_array(nonstatic_data_members_of(^^T, ctx)))
        {
            j[identifier_of(it)] = value.[:it:];
        }
    }

    template <typename T>
    static void from_json(const nlohmann::json &j, T &value)
    {
        constexpr auto ctx = std::meta::access_context::unchecked();

        template for (constexpr auto it : define_static_array(nonstatic_data_members_of(^^T, ctx)))
        {
            value.[:it:] = j[identifier_of(it)];
        }
    }
};
