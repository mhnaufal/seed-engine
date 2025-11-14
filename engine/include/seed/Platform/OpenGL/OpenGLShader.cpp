#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM

#include <OpenGLShader.h>
#include <Logger.h>

#include <glad.h>
#include <glm/gtc/type_ptr.hpp>

#include <array>
#include <filesystem>
#include <fstream>
#include <utility>
#include <vector>

namespace seed {
OpenGLShader::OpenGLShader(std::string  name, const char* vertex_source, const char* fragment_source) : m_name(std::move(name))
{
    std::unordered_map<GLenum, std::string> precompile;
    precompile[GL_VERTEX_SHADER] = vertex_source;
    precompile[GL_FRAGMENT_SHADER] = fragment_source;
    Compile(precompile);
}

OpenGLShader::OpenGLShader(const char* file_path)
{
    const auto source = ReadShaderFile(file_path);
    const auto shader_source = PreProcess(source);
    Compile(shader_source);

    const std::filesystem::path path_fs(file_path);
    m_name = path_fs.stem().string();
}

OpenGLShader::~OpenGLShader()
{
    glDeleteProgram(m_renderer_id);
}

auto OpenGLShader::ReadShaderFile(const char* file_path) -> std::string
{
    std::string source{};
    std::ifstream file(file_path, std::ios::in | std::ios::binary);
    if (file) {
        SEED_LOG_VERBOSE("Reading shader file");
        file.seekg(0, std::ios::end);
        source.resize(file.tellg());
        file.seekg(0, std::ios::beg);
        file.read(&source[0], static_cast<long long>(source.size()));
        file.close();
    } else {
        SEED_LOG_ERROR("Failed to open shader file: {}", file_path);
    }

    return source;
}

auto OpenGLShader::PreProcess(const std::string& shader_source) -> std::unordered_map<GLenum, std::string>
{
    std::unordered_map<GLenum, std::string> shader_map_source;
    const auto type_token = "#type";
    const size_t type_token_length = strlen(type_token);
    size_t pos = shader_source.find(type_token, 0);

    while (pos != std::string::npos) {
        const size_t eol = shader_source.find_first_of("\r\n", pos);

        const size_t begin = pos + type_token_length + 1;
        std::string type = shader_source.substr(begin, eol - begin);
        if (type != "vertex" && type != "fragment" && type != "pixel") {
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

auto OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shader_source) -> void
{
    const GLuint program = glCreateProgram();
    std::array<GLenum, 2> gl_shader_id{};
    int gl_shader_id_index = 0;

    for (const auto& [fst, snd] : shader_source) {
        const GLenum type = fst;
        const std::string key = snd;

        // [#] Create an empty vertex shader handle
        const GLuint shader_code = glCreateShader(type);
        const GLchar* source_cstr = snd.c_str();

        // [#] Send the vertex shader source code to GL
        auto source = source_cstr;
        glShaderSource(shader_code, 1, &source, nullptr);

        // [#] Compile the vertex shader
        glCompileShader(shader_code);

        GLint isCompiled = 0;
        glGetShaderiv(shader_code, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE) {
            GLint maxLength = 0;
            glGetShaderiv(shader_code, GL_INFO_LOG_LENGTH, &maxLength);

            // [#] The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(shader_code, maxLength, &maxLength, &infoLog[0]);

            // [#] We don't need the shader anymore.
            glDeleteShader(shader_code);

            // [#] Use the infoLog as you see fit.
            SEED_LOG_FATAL_ERROR("Failed to compile Shader: {}", infoLog.data());

            // [#] In this simple program, we'll just leave
            return;
        }

        // [#] Attach our shaders to our program
        glAttachShader(program, shader_code);
        gl_shader_id[gl_shader_id_index] = shader_code;
        gl_shader_id_index++;
    }

    // [#] Vertex and fragment shaders are successfully compiled.
    // [#] Now time to link them together into a program.
    // [#] Get a program object.
    m_renderer_id = program;

    // [#] Link our program
    glLinkProgram(program);

    // [#] Note the different functions here: glGetProgram* instead of glGetShader*.
    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
    if (isLinked == GL_FALSE) {
        GLint maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

        // [#] The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

        // [#] We don't need the program anymore.
        glDeleteProgram(program);

        // [#] Don't leak shaders either.
        for (const auto id : gl_shader_id) { glDeleteShader(id); }

        // [#] Use the infoLog as you see fit.
        SEED_LOG_FATAL_ERROR("Failed to link Shader: {}", infoLog.data());

        // [#] In this simple program, we'll just leave
        return;
    }

    // [#] Always detach shaders after a successful link.
    for (const auto id : gl_shader_id) { glDetachShader(program, id); }
}

auto OpenGLShader::Bind() const -> void
{
    glUseProgram(m_renderer_id);
}

auto OpenGLShader::Unbind() const -> void
{
    glUseProgram(0);
}

auto OpenGLShader::UploadUniformInt(const std::string& name, const int value) const -> void
{
    const GLint location = glGetUniformLocation(m_renderer_id, name.c_str());
    glUniform1i(location, value);
}

auto OpenGLShader::UploadUniformFloat(const std::string& name, const float value) const -> void
{
    const GLint location = glGetUniformLocation(m_renderer_id, name.c_str());
    glUniform1f(location, value);
}

auto OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& value) const -> void
{
    const GLint location = glGetUniformLocation(m_renderer_id, name.c_str());
    glUniform2f(location, value.x, value.y);
}

auto OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& value) const -> void
{
    const GLint location = glGetUniformLocation(m_renderer_id, name.c_str());
    glUniform3f(location, value.x, value.y, value.z);
}

auto OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& value) const -> void
{
    const GLint location = glGetUniformLocation(m_renderer_id, name.c_str());
    glUniform4f(location, value.x, value.y, value.z, value.w);
}

auto OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix) const -> void
{
    const GLint location = glGetUniformLocation(m_renderer_id, name.c_str());
    glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

auto OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix) const -> void
{
    const GLint location = glGetUniformLocation(m_renderer_id, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}
} // namespace seed