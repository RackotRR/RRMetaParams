#pragma once
#include <string>
#include <vector>
#include <optional>
#include <fstream>
#include <filesystem>
#include <functional>
#include <nlohmann/json.hpp>

#include "ModuleGenerator.h"
#include "ParametersBlock.h"

class HostParamsHeader : public ModuleGenerator {
public:
    HostParamsHeader(std::string classname, std::vector<ParametersBlock> parameter_blocks);
protected:
    void GenerateModuleCustom(std::ostream& stream) const override;
private:
    std::string classname;
    std::vector<ParametersBlock> parameter_blocks;
};

class ParamClass : public ModuleGenerator {
public:
    static ParamClass FromJson(const nlohmann::json& json);
    static ParamClass FromFile(const std::filesystem::path& path);
protected:
    void GenerateModuleCustom(std::ostream& stream) const override;
private:
    std::string classname;
    std::string filename;
    std::vector<ParametersBlock> parameter_blocks;
};