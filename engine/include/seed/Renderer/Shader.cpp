#include "Shader.h"

#include <Logger.h>
#include <Renderer.h>
#include <Platform/OpenGL/OpenGLShader.h>

namespace seed {
auto Shader::Create(const char* vertex_source, const char* fragment_source) -> Ref<Shader>
{
    switch (Renderer::GetRendererAPI()) {
    case RendererAPI::API::OPENGL:
        return std::make_shared<OpenGLShader>(vertex_source, fragment_source);
    case RendererAPI::API::SDL_GPU:
        SEED_LOG_ERROR("SDL_GPU Shader not implemented yet");
        return nullptr;
    case RendererAPI::API::NVRHI:
        SEED_LOG_ERROR("NVRHI Shader not implemented yet");
        return nullptr;
    default:
        return nullptr;
    }
}
} // namespace seed