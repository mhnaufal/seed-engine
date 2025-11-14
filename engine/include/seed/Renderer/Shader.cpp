#include <Shader.h>
#include <Logger.h>
#include <Renderer.h>
#include <Platform/OpenGL/OpenGLShader.h>

namespace seed {
auto Shader::Create(const std::string& name, const char* vertex_source, const char* fragment_source) -> Ref<Shader>
{
    switch (Renderer::GetRendererAPI()) {
    case RendererAPI::API::OPENGL:
        SEED_LOG_VERBOSE("Using OpenGL Shader");
        return std::make_shared<OpenGLShader>(name, vertex_source, fragment_source);
    case RendererAPI::API::SDL_GPU:
        SEED_LOG_FATAL_ERROR("SDL_GPU Shader not implemented yet");
        return nullptr;
    case RendererAPI::API::NVRHI:
        SEED_LOG_FATAL_ERROR("NVRHI Shader not implemented yet");
        return nullptr;
    default:
        return nullptr;
    }
}

auto Shader::Create(const char* file_path) -> Ref<Shader>
{
    switch (Renderer::GetRendererAPI()) {
    case RendererAPI::API::OPENGL:
        SEED_LOG_VERBOSE("Using OpenGL Shader");
        return std::make_shared<OpenGLShader>(file_path);
    case RendererAPI::API::SDL_GPU:
        SEED_LOG_FATAL_ERROR("SDL_GPU Shader not implemented yet");
        return nullptr;
    case RendererAPI::API::NVRHI:
        SEED_LOG_FATAL_ERROR("NVRHI Shader not implemented yet");
        return nullptr;
    default:
        return nullptr;
    }
}

auto ShaderLibrary::Add(const Ref<Shader>& shader) -> void
{
    const std::string name = shader->GetName();
    if (m_shaders.find(name) != m_shaders.end()) {
        SEED_LOG_ERROR("Shader {} already exists", name);
        return;
    }
    m_shaders[name] = shader;
}

auto ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader) -> void
{
    if (m_shaders.find(name) != m_shaders.end()) {
        SEED_LOG_ERROR("Shader {} already exists", name);
        return;
    }
    m_shaders[name] = shader;
}

auto ShaderLibrary::Load(const std::string& file_path) -> Ref<Shader>
{
    auto shader = Shader::Create(file_path.c_str());
    Add(shader);
    return shader;
}

auto ShaderLibrary::Load(const std::string& name, const std::string& file_path) -> Ref<Shader>
{
    auto shader = Shader::Create(file_path.c_str());
    Add(name, shader);
    return shader;
}

auto ShaderLibrary::Get(const std::string& name) -> Ref<Shader>
{
    if (m_shaders.find(name) == m_shaders.end()) {
        SEED_LOG_ERROR("Shader {} not exists", name);
        return nullptr;
    }
    return m_shaders[name];
}
} // namespace seed