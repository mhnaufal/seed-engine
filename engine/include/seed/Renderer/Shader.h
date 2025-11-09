#pragma once

#include "../Core/Definitions.h"

namespace seed {
class Shader {
public:
    virtual ~Shader() = default;

    virtual auto Bind() const -> void = 0;
    virtual auto Unbind() const -> void = 0;

    static auto Create(const char* vertex_source, const char* fragment_source) -> Ref<Shader>;
    static auto Create(const char* file_path) -> Ref<Shader>;
};
}