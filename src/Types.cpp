#include "Types.h"
#include <unordered_map>
#include <stdexcept>
#include <fmt/format.h>

static std::unordered_map<std::string, DataType> dataTypeFromStr{
    { "int", DataType::dt_int },
    { "uint", DataType::dt_uint },
    { "bool", DataType::dt_bool },
    { "enum", DataType::dt_enum },
    { "float", DataType::dt_float }
};
static std::unordered_map<DataType, std::string> dataTypeToStr{
    { DataType::dt_int, "rr_int" },
    { DataType::dt_uint, "rr_uint" },
    { DataType::dt_bool, "bool" },
    { DataType::dt_enum, "rr_uint" },
    { DataType::dt_float, "rr_float" }
};

DataType DataType_FromString(const std::string& str) {
    auto iter = dataTypeFromStr.find(str);
    if (iter == dataTypeFromStr.end()) {
        throw std::runtime_error{ "Wrong data type provided: " + str };
    }

    return iter->second;
}

std::string DataType_ToString(DataType type) {
    auto iter = dataTypeToStr.find(type);
    if (iter == dataTypeToStr.end()) {
        throw std::runtime_error{ "Wrong data type provided: " + std::to_string((int)type) };
    }

    return iter->second;
}

ValueType Value_FromJson(const nlohmann::json& json, DataType type) {
    switch (type) {
    case DataType::dt_int:
        return json.get<int>();
    case DataType::dt_uint:
        return json.get<unsigned>();
    case DataType::dt_bool:
        return json.get<bool>();
    case DataType::dt_enum:
        return json.get<int>();
    case DataType::dt_float:
        return json.get<double>();
    default:
        throw std::runtime_error{ "Wrong data type provided" };
    }
}

std::string Value_ToString(ValueType value, DataType type) {
    switch (type) {
    case DataType::dt_int:
        return std::to_string(std::get<int>(value));
    case DataType::dt_uint:
        return std::to_string(std::get<unsigned>(value));
    case DataType::dt_bool:
        return std::get<bool>(value) ? "true" : "false";
    case DataType::dt_enum:
        return std::to_string(std::get<int>(value));
    case DataType::dt_float:
        return fmt::format("{}", std::get<double>(value));
    default:
        throw std::runtime_error{ "Wrong data type provided" };
    }
}