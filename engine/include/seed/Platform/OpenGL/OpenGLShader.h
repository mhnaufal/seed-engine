#pragma once

#include "../../Renderer/Shader.h"

#include <glm/glm.hpp>
#include <string>
#include <cstdint>
#include <unordered_map>

// TODO: remove
#define GL_VERTEX_SHADER 0x8B31
#define GL_FRAGMENT_SHADER 0x8B30
typedef unsigned int GLenum;

namespace seed {
class OpenGLShader final : public Shader {
public:
    explicit OpenGLShader(std::string name, const char* vertex_source, const char* fragment_source);
    explicit OpenGLShader(const char* file_path);
    ~OpenGLShader() override;

    auto Bind() const -> void override;
    auto Unbind() const -> void override;

    auto SetUniformInt(const std::string& name, int value) -> void override;
    auto SetUniformFloat3(const std::string& name, const glm::vec3& value) -> void override;
    auto SetUniformFloat4(const std::string& name, const glm::vec4& value) -> void override;
    auto SetUniformMat4(const std::string& name, const glm::mat4& value) -> void override;

    [[nodiscard]] auto GetName() const -> std::string override { return m_name; };

    auto UploadUniformInt(const std::string& name, int value) const -> void;

    auto UploadUniformFloat(const std::string& name, float value) const -> void;
    auto UploadUniformFloat2(const std::string& name, const glm::vec2& value) const -> void;
    auto UploadUniformFloat3(const std::string& name, const glm::vec3& value) const -> void;
    auto UploadUniformFloat4(const std::string& name, const glm::vec4& value) const -> void;

    auto UploadUniformMat3(const std::string& name, const glm::mat3& matrix) const -> void;
    auto UploadUniformMat4(const std::string& name, const glm::mat4& matrix) const -> void;

private:
    static auto ReadShaderFile(const char* file_path) -> std::string;
    static auto PreProcess(const std::string& shader_source) -> std::unordered_map<GLenum, std::string>;
    auto Compile(const std::unordered_map<GLenum, std::string>& shader_source) -> void;

    static inline auto ShaderTypeFromString(const std::string& type) -> GLenum
    {
        if (type == "vertex") return GL_VERTEX_SHADER;
        if (type == "fragment" || type == "pixel") return GL_FRAGMENT_SHADER;
        return 0;
    }

private:
    uint32_t m_renderer_id{};
    std::string m_name{};
};
} // namespace seed