#include "Buffer.h"

#include "Logger.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace seed {
auto VertexBuffer::Create(const float* vertices, const uint32_t size) -> VertexBuffer*
{
    switch (Renderer::GetRendererAPI()) {
    case RendererAPI::OPENGL:
        return new OpenGLVertexBuffer(vertices, size);
    case RendererAPI::SDL_GPU:
        SEED_LOG_ERROR("SDL_GPU Renderer not implemented yet");
        return nullptr;
    case RendererAPI::NVRHI:
        SEED_LOG_ERROR("NVRHI Renderer not implemented yet");
        return nullptr;
    case RendererAPI::NONE:
        return nullptr;
    default:
        return nullptr;
    }
}

auto IndexBuffer::Create(const uint32_t* indices, const uint32_t size) -> IndexBuffer*
{
    switch (Renderer::GetRendererAPI()) {
    case RendererAPI::OPENGL:
        return new OpenGLIndexBuffer(indices, size);
    case RendererAPI::SDL_GPU:
        SEED_LOG_ERROR("SDL_GPU Renderer not implemented yet");
        return nullptr;
    case RendererAPI::NVRHI:
        SEED_LOG_ERROR("NVRHI Renderer not implemented yet");
        return nullptr;
    case RendererAPI::NONE:
        return nullptr;
    default:
        return nullptr;
    }
}
}