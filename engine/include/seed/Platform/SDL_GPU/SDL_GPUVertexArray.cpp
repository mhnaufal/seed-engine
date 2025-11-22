#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM

#include <SDL_GPUVertexArray.h>
#include <SDL_GPUBuffer.h>

namespace seed
{
    SDL_GPUVertexArray::SDL_GPUVertexArray()
    {
        SEED_PROFILE_FUNCTION();
    }

    SDL_GPUVertexArray::~SDL_GPUVertexArray()
    {
        SEED_PROFILE_FUNCTION();
    }

    auto SDL_GPUVertexArray::Bind() const -> void
    {
        SEED_PROFILE_FUNCTION();
    }

    auto SDL_GPUVertexArray::Unbind() const -> void
    {
        SEED_PROFILE_FUNCTION();
    }

    auto SDL_GPUVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertex_buffers) -> void
    {
        SEED_PROFILE_FUNCTION();

        uint32_t index = 0;
        const auto& i_layout = vertex_buffers->GetLayout();
        for (const auto& element : i_layout)
        {
        }
        m_vertex_buffers.push_back(vertex_buffers);
    }

    auto SDL_GPUVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& index_buffers) -> void
    {
        SEED_PROFILE_FUNCTION();

        index_buffers->Bind();
        m_index_buffers = index_buffers;
    }
} // namespace seed
