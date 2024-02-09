#include "Conditions.h"

Condition::Condition(std::string param_name) : param_name{ param_name }
{    
}

SingleValueCondition::SingleValueCondition(std::string param_name, ValueType need_value)
: Condition{ param_name }, need_value{ need_value }
{

}

MultipleCondition::MultipleCondition(std::string param_name, std::vector<ValueType> need_values) 
: Condition{ param_name }, need_values{need_values}
{
    
}

Conditions Conditions::FromJson(const nlohmann::json& json) {
    return Conditions{};
}