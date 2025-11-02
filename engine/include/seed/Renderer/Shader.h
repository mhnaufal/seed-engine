#pragma once

#include <glm/glm.hpp>
#include <string>

namespace seed {
class Shader final {
public:
    Shader(const std::string& vertex_src, const std::string& fragment_src);
    ~Shader();

    auto Bind() const -> void;
    static auto Unbind() -> void;
    auto UploadUniformMat4(const std::string& name, const glm::mat4& matrix) const -> void;
private:
    uint32_t m_renderer_id{};
};
}