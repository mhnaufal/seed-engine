#pragma once

#include <string>

namespace seed {
class Shader final {
public:
    Shader(const std::string& vertex_src, const std::string& fragment_src);
    ~Shader();

    auto Bind() -> void;
    auto Unbind() -> void;
private:
    uint32_t m_renderer_id{};
};
}