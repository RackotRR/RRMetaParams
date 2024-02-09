#pragma once
#include <ostream>
#include <functional>
#include <filesystem>

class ModuleGenerator {
public:
    using GeneratePartCallback = std::function<void(std::ostream& stream)>;

    void GenerateModule(std::ostream& stream) const;
    void GenerateModuleFile(const std::filesystem::path& path) const;

    void SetLineStart(const std::string& line_start);
    void SetPasteBeforeCallback(GeneratePartCallback paste_before);
    void SetPasteAfterCallback(GeneratePartCallback paste_after);
protected:
    virtual void GenerateModuleCustom(std::ostream& stream) const = 0;
    virtual void SetLineStartCustom(const std::string& line_start) {}
    virtual void SetPasteBeforeCallbackCustom(GeneratePartCallback paste_before) {}
    virtual void SetPasteAfterCallbackCustom(GeneratePartCallback paste_after) {}

    std::string line_start;
private:
    GeneratePartCallback paste_before;
    GeneratePartCallback paste_after;
};