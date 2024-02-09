#include "Parameter.h"
#include <fmt/format.h>
#include <iostream>

Parameter Parameter::FromJson(std::string name, const nlohmann::json& json) {
    Parameter parameter;
    parameter.name = std::move(name);
    parameter.data_type = DataType_FromString(json.at("data_type").get<std::string>());

    if (json.contains("block")) {
        parameter.block = json.at("block").get<std::string>();
    }
    else {
        parameter.block = parameter.name;
    }

    if (json.contains("default_value")) {
        parameter.default_value = Value_FromJson(json.at("default_value"), parameter.data_type);
    }

    if (json.contains("conditions")) {
        parameter.conditions = Conditions::FromJson(json.at("conditions"));
    }

    if (json.contains("constraint")) {
        if (parameter.data_type != DataType::dt_enum) {
            throw std::runtime_error{ "Error using constraint without enum data type" };
        }

        //throw std::runtime_error{ "Not implemented" };
    }

    if (json.contains("min")) {
        if (parameter.data_type == DataType::dt_bool) {
            throw std::runtime_error{ "Error using min with bool data type" };
        }

        parameter.min = Value_FromJson(json.at("min"), parameter.data_type);
    }
    if (json.contains("max")) {
        if (parameter.data_type == DataType::dt_bool) {
            throw std::runtime_error{ "Error using max with bool data type" };
        }

        parameter.max = Value_FromJson(json.at("max"), parameter.data_type);
    }

    if (json.contains("description")) {
        parameter.description = json.at("description").get<std::string>();
    }

    std::cout << "Parameter " << parameter.name << " loaded" << std::endl;
    return parameter;
}


void Parameter::GenerateModuleCustom(std::ostream& stream) const {
    if (description.has_value()) {
        stream << fmt::format("{}/* {} */", line_start, description.value()) << std::endl;
    }

    std::string data_type_str = DataType_ToString(data_type);
    std::string default_value_part = default_value.has_value() ?
        fmt::format(" = {}", Value_ToString(default_value.value(), data_type)) :
        "{}";

    stream << fmt::format("{}{} {}{};",
        line_start,
        data_type_str,
        name,
        default_value_part) << std::endl;
}