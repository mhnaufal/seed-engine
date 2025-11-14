#include <VertexArray.h>
#include <Renderer.h>
#include <Logger.h>
#include <Platform/OpenGL/OpenGLVertexArray.h>

namespace seed {
auto VertexArray::Create() -> Ref<VertexArray>
{
    switch (Renderer::GetRendererAPI()) {
    case RendererAPI::API::OPENGL:
        SEED_LOG_VERBOSE("Using OpenGL Vertex Array");
        return std::make_shared<OpenGLVertexArray>();
    case RendererAPI::API::SDL_GPU:
        SEED_LOG_FATAL_ERROR("SDL_GPU Vertex Array Renderer not implemented yet");
        return nullptr;
    case RendererAPI::API::NVRHI:
        SEED_LOG_FATAL_ERROR("NVRHI Vertex Array Renderer not implemented yet");
        return nullptr;
    default:
        return nullptr;
    }
}
}