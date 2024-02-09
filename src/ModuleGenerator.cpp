#include "ModuleGenerator.h"
#include <fstream>

void ModuleGenerator::GenerateModule(std::ostream& stream) const {
    if (paste_before) {
        paste_before(stream);
    }

    GenerateModuleCustom(stream);

    if (paste_after) {
        paste_after(stream);
    }
}

void ModuleGenerator::GenerateModuleFile(const std::filesystem::path& path) const {
    std::ofstream stream{ path };
    if (!stream) {
        throw std::runtime_error{ "GenerateModule error. Can't open file: " + path.string() };
    }

    GenerateModule(stream);
}

void ModuleGenerator::SetLineStart(const std::string& line_start) {
    this->line_start = line_start;
    SetLineStartCustom(line_start);
}
void ModuleGenerator::SetPasteBeforeCallback(GeneratePartCallback paste_before) {
    this->paste_before = paste_before;
    SetPasteBeforeCallbackCustom(paste_before);
}
void ModuleGenerator::SetPasteAfterCallback(GeneratePartCallback paste_after) {
    this->paste_after = paste_after;
    SetPasteAfterCallbackCustom(paste_after);
}