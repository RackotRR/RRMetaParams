#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <filesystem>
#include <functional>
#include <nlohmann/json.hpp>

#include "ModuleGenerator.h"

// this class represents possible enumeration values
class Constraint : public ModuleGenerator {
public:
    std::string Name() const;
    bool Check(int value) const;

    static Constraint FromJson(std::string name, const nlohmann::json& json);
protected:
    void GenerateModuleCustom(std::ostream& stream) const override;
private:
    std::string name;
    std::string prefix;
    std::vector<std::string> values;
};

// this class represents a header with enumerations
class Constraints : public ModuleGenerator {
public:
    using GeneratePartCallback = std::function<void(std::ofstream& stream)>;

    Constraint Find(const std::string& name);

    static Constraints FromJson(const nlohmann::json& json);
    static Constraints FromFile(const std::filesystem::path& path);
protected:
    void GenerateModuleCustom(std::ostream& stream) const override;
private:
    Constraints() = default;
    std::unordered_map<std::string, Constraint> constraints;
};