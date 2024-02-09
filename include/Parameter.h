#pragma once
#include <string>
#include <optional>
#include "Types.h"
#include "Constraints.h"
#include "Conditions.h"
#include "ModuleGenerator.h"

class Parameter : public ModuleGenerator {
public:
    static Parameter FromJson(std::string name, const nlohmann::json& json);
protected:
    void GenerateModuleCustom(std::ostream& stream) const override;
private:
    std::string name;
    DataType data_type;
    std::string block;
    std::optional<ValueType> default_value;
    std::optional<std::string> constraint;
    std::optional<Conditions> conditions;
    std::optional<ValueType> min;
    std::optional<ValueType> max;
    std::optional<std::string> description;
};
