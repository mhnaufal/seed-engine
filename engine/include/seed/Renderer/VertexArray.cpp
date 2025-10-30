#include "VertexArray.h"
#include "Renderer.h"
#include "Logger.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace seed {
auto VertexArray::Create() -> VertexArray*
{
    switch (Renderer::GetRendererAPI()) {
    case RendererAPI::API::OPENGL:
        return new OpenGLVertexArray();
    case RendererAPI::API::SDL_GPU:
        SEED_LOG_ERROR("SDL_GPU Vertex Array Renderer not implemented yet");
        return nullptr;
    case RendererAPI::API::NVRHI:
        SEED_LOG_ERROR("NVRHI Vertex Array Renderer not implemented yet");
        return nullptr;
    default:
        return nullptr;
    }
}
}