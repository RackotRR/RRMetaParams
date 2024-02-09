#include "Constraints.h"
#include <stdexcept>
#include <fmt/format.h>

std::string Constraint::Name() const {
    return name;
}

bool Constraint::Check(int value) const {
    return value >= 0 && value < values.size();
}

void Constraint::GenerateModuleCustom(std::ostream& stream) const {
    int num_value = 0;
    for (auto& value : values) {
        stream << fmt::format("#define {}_{} {}",
            prefix, 
            value,
            num_value) << std::endl;
        
        ++num_value;
    }
}

Constraint Constraint::FromJson(std::string name, const nlohmann::json& json) {
    Constraint constraint;
    
    constraint.name = std::move(name);
    constraint.prefix = json.at("prefix").get<std::string>();
    
    for (auto& value_data : json.at("values")) {
        constraint.values.push_back(value_data.get<std::string>());
    }

    return constraint;
}

Constraints Constraints::FromJson(const nlohmann::json& json) {
    Constraints constraints;

    for (auto& [name, constraint] : json.items()) {
        constraints.constraints.emplace(name, Constraint::FromJson(name, constraint));
    }

    constraints.SetPasteBeforeCallback([](std::ostream& stream) {
        stream << "#pragma once" << std::endl << std::endl;
    });
    return constraints;
}
Constraints Constraints::FromFile(const std::filesystem::path& path) {
    std::ifstream stream{ path };
    if (!stream) {
        throw std::runtime_error{ "Constraints::FromJson error. Can't open file: " + path.string() };
    }

    nlohmann::json json;
    stream >> json;

    return FromJson(json);
}

void Constraints::GenerateModuleCustom(std::ostream& stream) const {
    for (auto& [name, constraint] : constraints) {
        constraint.GenerateModule(stream);
        stream << std::endl;
    }
}

Constraint Constraints::Find(const std::string& name) {
    return constraints.at(name);
}