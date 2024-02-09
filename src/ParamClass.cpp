#include "ParamClass.h"
#include <fstream>
#include <fmt/format.h>


HostParamsHeader::HostParamsHeader(std::string classname, std::vector<ParametersBlock> parameter_blocks) 
    : 
    classname{ std::move(classname) }, 
    parameter_blocks{ std::move(parameter_blocks) } 
{
    for (auto& block : parameter_blocks) {
        block.SetLineStart("\t");
    }
}

void HostParamsHeader::GenerateModuleCustom(std::ostream& stream) const {
    
}



ParamClass ParamClass::FromJson(const nlohmann::json& json) {
    ParamClass param_class;
    param_class.classname = json.at("classname").get<std::string>();

    if (json.contains("filename")) {
        param_class.filename = json.at("filename").get<std::string>();
    }
    else {
        param_class.filename = param_class.classname;
    }

    for (auto& [block_name, block_data] : json.at("parameters").items()) {
        auto block = ParametersBlock::FromJson(block_name, block_data);
        block.SetLineStart("\t");
        param_class.parameter_blocks.push_back(std::move(block));
    }

    param_class.SetPasteBeforeCallback([](std::ostream& stream){
        stream << "#pragma once" << std::endl;
        stream << std::endl;
        stream << "using rr_float = double;" << std::endl;
        stream << "using rr_uint = unsigned;" << std::endl;
        stream << "using rr_int = int;" << std::endl;
        stream << std::endl;
    });

    return param_class;
}

ParamClass ParamClass::FromFile(const std::filesystem::path& path) {
    std::ifstream stream{ path };
    if (!stream) {
        throw std::runtime_error{ "ParamClass::FromJson error. Can't open file: " + path.string() };
    }

    nlohmann::json json;
    stream >> json;

    return FromJson(json);
}

void ParamClass::GenerateModuleCustom(std::ostream& stream) const {
    stream << fmt::format("struct {} ", classname) << "{" << std::endl;
    stream << '\t' << fmt::format("static constexpr const char* filename = \"{}\";", filename) << std::endl;
    stream << std::endl;
    for (auto& block : parameter_blocks) {
        block.GenerateModule(stream);
        stream << std::endl;
    }
    stream << "};" << std::endl;
}