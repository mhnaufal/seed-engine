#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM

#include <OpenGLShader.h>
#include <Logger.h>

#include <glad.h>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

namespace seed {
OpenGLShader::OpenGLShader(const char* vertex_source, const char* fragment_source)
{
    // /* 🐤 TODO: change to SDL
    // [#] Create an empty vertex shader handle
    const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // [#] Send the vertex shader source code to GL
    auto source = vertex_source;
    glShaderSource(vertexShader, 1, &source, nullptr);

    // [#] Compile the vertex shader
    glCompileShader(vertexShader);

    GLint isCompiled = 0;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

        // [#] The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

        // [#] We don't need the shader anymore.
        glDeleteShader(vertexShader);

        // [#] Use the infoLog as you see fit.
        SEED_LOG_ERROR("Failed to compile vertex shader: {}", infoLog.data());

        // [#] In this simple program, we'll just leave
        return;
    }

    // [#] Create an empty fragment shader handle
    const GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // [#] Send the fragment shader source code to GL
    // [#] Note that std::string's .c_str is NULL character terminated.
    source = fragment_source;
    glShaderSource(fragmentShader, 1, &source, nullptr);

    // [#] Compile the fragment shader
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

        // [#] The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

        // [#] We don't need the shader anymore.
        glDeleteShader(fragmentShader);
        // [#] Either of them. Don't leak shaders.
        glDeleteShader(vertexShader);

        // [#] Use the infoLog as you see fit.
        SEED_LOG_ERROR("Failed to compile fragment shader: {}", infoLog.data());

        // [#] In this simple program, we'll just leave
        return;
    }

    // [#] Vertex and fragment shaders are successfully compiled.
    // [#] Now time to link them together into a program.
    // [#] Get a program object.
    m_renderer_id = glCreateProgram();
    const auto program = m_renderer_id;

    // [#] Attach our shaders to our program
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

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
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        // [#] Use the infoLog as you see fit.
        SEED_LOG_ERROR("Failed to link shader: {}", infoLog.data());

        // [#] In this simple program, we'll just leave
        return;
    }

    // [#] Always detach shaders after a successful link.
    glDetachShader(program, vertexShader);
    glDetachShader(program, fragmentShader);
    // 🐤 TODO: change to SDL */
}

OpenGLShader::~OpenGLShader()
{
    glDeleteProgram(m_renderer_id);
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