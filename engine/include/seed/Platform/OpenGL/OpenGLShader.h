#pragma once

#include "../../Renderer/Shader.h"

#include <glm/glm.hpp>
#include <string>
#include <cstdint>

namespace seed {
class OpenGLShader final : public Shader {
public:
    explicit OpenGLShader(const char* vertex_source, const char* fragment_source);
    ~OpenGLShader() override;

    auto Bind() const -> void override;
    auto Unbind() const -> void override;

    auto UploadUniformInt(const std::string& name, const int value) const -> void;

    auto UploadUniformFloat(const std::string& name, const float value) const -> void;
    auto UploadUniformFloat2(const std::string& name, const glm::vec2& value) const -> void;
    auto UploadUniformFloat3(const std::string& name, const glm::vec3& value) const -> void;
    auto UploadUniformFloat4(const std::string& name, const glm::vec4& value) const -> void;

    auto UploadUniformMat3(const std::string& name, const glm::mat3& matrix) const -> void;
    auto UploadUniformMat4(const std::string& name, const glm::mat4& matrix) const -> void;

private:
    uint32_t m_renderer_id{};
};
} // namespace seed