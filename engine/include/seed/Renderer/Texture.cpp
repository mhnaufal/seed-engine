#include <Logger.h>
#include <Texture.h>
#include <Renderer.h>
#include <Platform/OpenGL/OpenGLTexture.h>

namespace seed {
auto Texture2D::Create(const std::string& path) -> Ref<Texture2D>
{
    switch (Renderer::GetRendererAPI()) {
    case RendererAPI::API::OPENGL:
        return std::make_shared<OpenGLTexture2D>(path);
    case RendererAPI::API::SDL_GPU:
        SEED_LOG_ERROR("SDL_GPU Texture not implemented yet");
        return nullptr;
    case RendererAPI::API::NVRHI:
        SEED_LOG_ERROR("NVRHI Texture not implemented yet");
        return nullptr;
    default:
        return nullptr;
    }
}
}