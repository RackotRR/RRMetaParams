#pragma once
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

#include "Types.h"

// base class for parameter requirements for other parameters
class Condition {
protected:
    Condition(std::string param_name);
    std::string param_name;
};

// requirement for one matching value
class SingleValueCondition : Condition {
public:
    SingleValueCondition(std::string param_name, ValueType need_value);
private:
    ValueType need_value;
};

// requirement for several possible values from enumeration
class MultipleCondition : Condition {
public:
    MultipleCondition(std::string param_name, std::vector<ValueType> need_values);
private:
    std::vector<ValueType> need_values;
};

// there could be several parameters requirements
class Conditions {
public:
    static Conditions FromJson(const nlohmann::json& json);
private:
    std::vector<Condition> conditions;
};