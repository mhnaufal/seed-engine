#pragma once

#include "../Core/Definitions.h"

#include <string>
#include <unordered_map>

namespace seed {
class Shader {
public:
    virtual ~Shader() = default;

    virtual auto Bind() const -> void = 0;
    virtual auto Unbind() const -> void = 0;

    [[nodiscard]] virtual auto GetName() const -> std::string = 0;

    static auto Create(const std::string& name, const char* vertex_source, const char* fragment_source) -> Ref<Shader>;
    static auto Create(const char* file_path) -> Ref<Shader>;
};

class ShaderLibrary {
public:
    auto Add(const Ref<Shader>& shader) -> void;
    auto Add(const std::string& name, const Ref<Shader>& shader) -> void;
    auto Load(const std::string& file_path) -> Ref<Shader>;
    auto Load(const std::string& name, const std::string& file_path) -> Ref<Shader>;
    auto Get(const std::string& name) -> Ref<Shader>;

private:
    std::unordered_map<std::string, Ref<Shader>> m_shaders{};
};
}