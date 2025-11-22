#include "SDL_GPUBuffer.h"

namespace seed
{
    // ===================================
    // Vertex Buffer ====================
    // ===================================

    SDL_GPUVertexBuffer::SDL_GPUVertexBuffer([[maybe_unused]] const float* vertices,
                                             [[maybe_unused]] const uint32_t size)
    {
        SEED_PROFILE_FUNCTION();

    }

    SDL_GPUVertexBuffer::~SDL_GPUVertexBuffer()
    {
        SEED_PROFILE_FUNCTION();

    }

    auto SDL_GPUVertexBuffer::Bind() const -> void
    {
        SEED_PROFILE_FUNCTION();

    }

    auto SDL_GPUVertexBuffer::Unbind() const -> void
    {
        SEED_PROFILE_FUNCTION();

    }

    [[nodiscard]] auto SDL_GPUVertexBuffer::GetLayout() const -> BufferLayout
    {
        return BufferLayout{};
    }

    auto SDL_GPUVertexBuffer::SetLayout([[maybe_unused]] const BufferLayout& layout) -> void
    {
    }

    // ===================================
    // Index Buffer ======================
    // ===================================

    SDL_GPUIndexBuffer::SDL_GPUIndexBuffer([[maybe_unused]] const uint32_t* indices, const uint32_t size)
        : m_count(size)
    {
        SEED_PROFILE_FUNCTION();

    }

    SDL_GPUIndexBuffer::~SDL_GPUIndexBuffer()
    {
        SEED_PROFILE_FUNCTION();

    }

    auto SDL_GPUIndexBuffer::Bind() const -> void
    {
        SEED_PROFILE_FUNCTION();

    }

    auto SDL_GPUIndexBuffer::Unbind() const -> void
    {
        SEED_PROFILE_FUNCTION();

    }

    auto SDL_GPUIndexBuffer::GetCount() const -> uint32_t
    {
        return 0;
    }
} // namespace seed
