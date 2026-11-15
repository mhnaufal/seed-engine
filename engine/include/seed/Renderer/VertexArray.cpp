#include <VertexArray.h>
#include <Renderer.h>
#include <Logger.h>
// #include <Platform/OpenGL/OpenGLVertexArray.h>
#include <Platform/SDL_GPU/SDL_GPUVertexArray.h>

namespace seed
{
    auto VertexArray::Create() -> Ref<VertexArray>
    {
        switch (Renderer::GetRendererAPI())
        {
        // case RendererAPI::API::OPENGL:
        //     SEED_LOG_VERBOSE("Using OpenGL Vertex Array");
        //     return std::make_shared<OpenGLVertexArray>();
        case RendererAPI::API::SDL_GPU:
            SEED_LOG_VERBOSE("Using SDL GPU Vertex Array");
            return std::make_shared<SDL_GPUVertexArray>();
        case RendererAPI::API::NVRHI:
            SEED_LOG_FATAL_ERROR("NVRHI Vertex Array Renderer not implemented yet");
            return nullptr;
        default:
            return nullptr;
        }
    }
}
