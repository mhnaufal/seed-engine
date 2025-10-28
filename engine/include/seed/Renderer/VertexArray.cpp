#include "VertexArray.h"
#include "Renderer.h"
#include "Logger.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace seed {
auto VertexArray::Create() -> VertexArray*
{
    switch (Renderer::GetRendererAPI()) {
    case RendererAPI::OPENGL:
        return new OpenGLVertexArray();
    case RendererAPI::SDL_GPU:
        SEED_LOG_ERROR("SDL_GPU Vertex Array Renderer not implemented yet");
        return nullptr;
    case RendererAPI::NVRHI:
        SEED_LOG_ERROR("NVRHI Vertex Array Renderer not implemented yet");
        return nullptr;
    default:
        return nullptr;
    }
}
}