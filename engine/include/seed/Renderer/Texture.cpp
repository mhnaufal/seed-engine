#include <Logger.h>
#include <Texture.h>
#include <Renderer.h>
#include <Platform/OpenGL/OpenGLTexture.h>

namespace seed {
auto Texture2D::Create(const std::string& path) -> Ref<Texture2D>
{
    switch (Renderer::GetRendererAPI()) {
    case RendererAPI::API::OPENGL:
        SEED_LOG_VERBOSE("Using OpenGL Texture");
        return std::make_shared<OpenGLTexture2D>(path);
    case RendererAPI::API::SDL_GPU:
        SEED_LOG_FATAL_ERROR("SDL_GPU Texture not implemented yet");
        return nullptr;
    case RendererAPI::API::NVRHI:
        SEED_LOG_FATAL_ERROR("NVRHI Texture not implemented yet");
        return nullptr;
    default:
        return nullptr;
    }
}

auto Texture2D::Create(uint32_t width, uint32_t height) -> Ref<Texture2D>
{
    switch (Renderer::GetRendererAPI()) {
    case RendererAPI::API::OPENGL:
        SEED_LOG_VERBOSE("Using OpenGL Texture");
        return std::make_shared<OpenGLTexture2D>(width, height);
    case RendererAPI::API::SDL_GPU:
        SEED_LOG_FATAL_ERROR("SDL_GPU Texture not implemented yet");
        return nullptr;
    case RendererAPI::API::NVRHI:
        SEED_LOG_FATAL_ERROR("NVRHI Texture not implemented yet");
        return nullptr;
    default:
        return nullptr;
    }
}

}