#include "Shader.h"

#include <Logger.h>
#include <SDL3/SDL.h>
#include <vector>

#include "imgui_impl_opengl3_loader.h"

namespace seed {
Shader::Shader(const std::string& vertex_src, const std::string& fragment_src)
{
    // /* 🐤 TODO: change to SDL
    // [#] Create an empty vertex shader handle
    const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // [#] Send the vertex shader source code to GL
    // [#] Note that std::string's .c_str is NULL character terminated.
    auto source = vertex_src.c_str();
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
    source = fragment_src.c_str();
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

Shader::~Shader()
{
    glDeleteProgram(m_renderer_id);
}

auto Shader::Bind() -> void
{
    glUseProgram(m_renderer_id);
}

auto Shader::Unbind() -> void
{
    glUseProgram(0);
}
} // namespace seed