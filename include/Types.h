#pragma once
#include <string>
#include <variant>
#include <nlohmann/json.hpp>

using ValueType = std::variant<int, unsigned, bool, double>;
enum class DataType {
    dt_int,
    dt_uint,
    dt_bool,
    dt_enum,
    dt_float
};

DataType DataType_FromString(const std::string& str);
std::string DataType_ToString(DataType type);

ValueType Value_FromJson(const nlohmann::json& json, DataType type);
std::string Value_ToString(ValueType value, DataType type);