#include "ParametersBlock.h"
#include <fmt/format.h>

ParametersBlock ParametersBlock::FromJson(std::string name, const nlohmann::json& json) {
    ParametersBlock block;
    block.name = std::move(name);

    for (auto& [param_name, param_data] : json.items()) {
        block.parameters.push_back(Parameter::FromJson(param_name, param_data));
    }

    return block;
}

void ParametersBlock::GenerateModuleCustom(std::ostream& stream) const {
    std::string comment = fmt::format("{}// ", line_start);
    stream << comment << fmt::format("{:-^40}", "") << std::endl;
    stream << comment << fmt::format("{:-^40}", name) << std::endl;
    stream << comment << fmt::format("{:-^40}", "") << std::endl;

    for (auto& param : parameters) {
        param.GenerateModule(stream);
    }
}

void ParametersBlock::SetLineStartCustom(const std::string& line_start) {
    for (auto& param : parameters) {
        param.SetLineStart(line_start);
    }
}