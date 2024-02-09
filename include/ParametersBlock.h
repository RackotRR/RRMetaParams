#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>
#include "Parameter.h"
#include "ModuleGenerator.h"

class ParametersBlock : public ModuleGenerator {
public:
    static ParametersBlock FromJson(std::string name, const nlohmann::json& json);
protected:
    void GenerateModuleCustom(std::ostream& stream) const override;
    void SetLineStartCustom(const std::string& line_start) override;
private:
    std::string name;
    std::vector<Parameter> parameters;
};