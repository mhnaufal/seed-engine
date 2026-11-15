#include <SDL_GPUShader.h>
#include <Logger.h>

// #include <glad.h>
#include <glm/gtc/type_ptr.hpp>

#include <array>
#include <filesystem>
#include <fstream>
#include <utility>
#include <vector>

namespace seed
{
    SDL_GPUShader::SDL_GPUShader(std::string name, const char* vertex_source, const char* fragment_source)
        : m_name(std::move(name))
    {
        SEED_PROFILE_FUNCTION();

        std::unordered_map<GLenum, std::string> precompile;
        precompile[GL_VERTEX_SHADER] = vertex_source;
        precompile[GL_FRAGMENT_SHADER] = fragment_source;
        Compile(precompile);
    }

    SDL_GPUShader::SDL_GPUShader(const char* file_path)
    {
        SEED_PROFILE_FUNCTION();

        const auto source = ReadShaderFile(file_path);
        const auto shader_source = PreProcess(source);
        Compile(shader_source);

        const std::filesystem::path path_fs(file_path);
        m_name = path_fs.stem().string();
    }

    SDL_GPUShader::~SDL_GPUShader()
    {
        SEED_PROFILE_FUNCTION();
    }

    auto SDL_GPUShader::ReadShaderFile(const char* file_path) -> std::string
    {
        SEED_PROFILE_FUNCTION();

        std::string source{};
        std::ifstream file(file_path, std::ios::in | std::ios::binary);
        if (file)
        {
            SEED_LOG_VERBOSE("Reading shader file");
            file.seekg(0, std::ios::end);
            source.resize(file.tellg());
            file.seekg(0, std::ios::beg);
            file.read(&source[0], static_cast<long long>(source.size()));
            file.close();
        }
        else
        {
            SEED_LOG_ERROR("Failed to open shader file: {}", file_path);
        }

        return source;
    }

    auto SDL_GPUShader::PreProcess(const std::string& shader_source) -> std::unordered_map<GLenum, std::string>
    {
        SEED_PROFILE_FUNCTION();

        std::unordered_map<GLenum, std::string> shader_map_source;
        const auto type_token = "#type";
        const size_t type_token_length = strlen(type_token);
        size_t pos = shader_source.find(type_token, 0);

        while (pos != std::string::npos)
        {
            const size_t eol = shader_source.find_first_of("\r\n", pos);

            const size_t begin = pos + type_token_length + 1;
            std::string type = shader_source.substr(begin, eol - begin);
            if (type != "vertex" && type != "fragment" && type != "pixel")
            {
                SEED_LOG_FATAL_ERROR("Unsupported shader type: {}", type);
                return shader_map_source;
            }

            const size_t next_line_pos = shader_source.find_first_not_of("\r\n", eol);
            pos = shader_source.find(type_token, next_line_pos);
            shader_map_source[ShaderTypeFromString(type)] = shader_source.substr(
                next_line_pos,
                pos - (next_line_pos == std::string::npos ? shader_source.size() - 1 : next_line_pos)
            );
        }

        return shader_map_source;
    }

    auto SDL_GPUShader::Compile(const std::unordered_map<GLenum, std::string>& shader_source) -> void
    {
        SEED_PROFILE_FUNCTION();
    }

    auto SDL_GPUShader::Bind() const -> void
    {
        SEED_PROFILE_FUNCTION();

        if (m_name.empty())
        {
            SEED_LOG_ERROR("Shader not loaded yet!");
        }
    }

    auto SDL_GPUShader::Unbind() const -> void
    {
        SEED_PROFILE_FUNCTION();

        if (m_name.empty())
        {
            SEED_LOG_FATAL_ERROR("Shader not loaded yet!");
        }
    }

    auto SDL_GPUShader::SetUniformInt(const std::string& name, int value) -> void
    {
        SEED_PROFILE_FUNCTION();

        UploadUniformInt(name, value);
    }

    auto SDL_GPUShader::SetUniformFloat(const std::string& name, float value) -> void
    {
        SEED_PROFILE_FUNCTION();

        UploadUniformFloat(name, value);
    }

    auto SDL_GPUShader::SetUniformFloat3(const std::string& name, const glm::vec3& value) -> void
    {
        SEED_PROFILE_FUNCTION();

        UploadUniformFloat3(name, value);
    }

    auto SDL_GPUShader::SetUniformFloat4(const std::string& name, const glm::vec4& value) -> void
    {
        SEED_PROFILE_FUNCTION();

        UploadUniformFloat4(name, value);
    }

    auto SDL_GPUShader::SetUniformMat4(const std::string& name, const glm::mat4& value) -> void
    {
        SEED_PROFILE_FUNCTION();

        UploadUniformMat4(name, value);
    }

    auto SDL_GPUShader::UploadUniformInt(const std::string& name, const int value) const -> void
    {
        SEED_PROFILE_FUNCTION();

        if (m_name.empty())
        {
            SEED_LOG_FATAL_ERROR("Shader not loaded yet!");
        }
    }

    auto SDL_GPUShader::UploadUniformFloat(const std::string& name, const float value) const -> void
    {
        SEED_PROFILE_FUNCTION();

        if (m_name.empty())
        {
            SEED_LOG_FATAL_ERROR("Shader not loaded yet!");
        }
    }

    auto SDL_GPUShader::UploadUniformFloat2(const std::string& name, const glm::vec2& value) const -> void
    {
        SEED_PROFILE_FUNCTION();

        if (m_name.empty())
        {
            SEED_LOG_FATAL_ERROR("Shader not loaded yet!");
        }
    }

    auto SDL_GPUShader::UploadUniformFloat3(const std::string& name, const glm::vec3& value) const -> void
    {
        SEED_PROFILE_FUNCTION();

        if (m_name.empty())
        {
            SEED_LOG_FATAL_ERROR("Shader not loaded yet!");
        }
    }

    auto SDL_GPUShader::UploadUniformFloat4(const std::string& name, const glm::vec4& value) const -> void
    {
        SEED_PROFILE_FUNCTION();

        if (m_name.empty())
        {
            SEED_LOG_FATAL_ERROR("Shader not loaded yet!");
        }
    }

    auto SDL_GPUShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix) const -> void
    {
        SEED_PROFILE_FUNCTION();

        if (m_name.empty())
        {
            SEED_LOG_FATAL_ERROR("Shader not loaded yet!");
        }
    }

    auto SDL_GPUShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix) const -> void
    {
        SEED_PROFILE_FUNCTION();

        if (m_name.empty())
        {
            SEED_LOG_FATAL_ERROR("Shader not loaded yet!");
        }
    }
} // namespace seed
