#include <Buffer.h>
#include <Logger.h>
#include <Renderer.h>
#include <Platform/OpenGL/OpenGLBuffer.h>

namespace seed {
auto BufferLayout::CalculateOffsetAndStride() -> void
{
    uint32_t offset = 0;
    m_stride = 0;
    for (auto& element : m_elements) {
        element.offset = offset;
        offset = offset + element.size;
        m_stride = m_stride + element.size;
    }
}

auto VertexBuffer::Create(const float* vertices, const uint32_t size) -> Ref<VertexBuffer>
{
    switch (Renderer::GetRendererAPI()) {
    case RendererAPI::API::OPENGL:
        SEED_LOG_VERBOSE("Using OpenGL Vertex Buffer");
        return std::make_shared<OpenGLVertexBuffer>(vertices, size);
    case RendererAPI::API::SDL_GPU:
        SEED_LOG_FATAL_ERROR("SDL_GPU Renderer not implemented yet");
        return nullptr;
    case RendererAPI::API::NVRHI:
        SEED_LOG_FATAL_ERROR("NVRHI Renderer not implemented yet");
        return nullptr;
    default:
        return nullptr;
    }
}

auto IndexBuffer::Create(const uint32_t* indices, const uint32_t size) -> Ref<IndexBuffer>
{
    switch (Renderer::GetRendererAPI()) {
    case RendererAPI::API::OPENGL:
        SEED_LOG_VERBOSE("Using OpenGL Index Buffer");
        return std::make_shared<OpenGLIndexBuffer>(indices, size);
    case RendererAPI::API::SDL_GPU:
        SEED_LOG_FATAL_ERROR("SDL_GPU Renderer not implemented yet");
        return nullptr;
    case RendererAPI::API::NVRHI:
        SEED_LOG_FATAL_ERROR("NVRHI Renderer not implemented yet");
        return nullptr;
    default:
        return nullptr;
    }
}
}