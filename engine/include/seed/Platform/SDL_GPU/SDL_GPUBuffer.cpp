#include "SDL_GPUBuffer.h"

namespace seed {
// ===================================
// Vertex Buffer ====================
// ===================================

SDL_GPUVertexBuffer::SDL_GPUVertexBuffer([[maybe_unused]] const float* vertices, [[maybe_unused]] const uint32_t size)
{
}

SDL_GPUVertexBuffer::~SDL_GPUVertexBuffer()
{
}

auto SDL_GPUVertexBuffer::Bind() const -> void
{
}

auto SDL_GPUVertexBuffer::Unbind() const -> void
{
}

// ===================================
// Index Buffer ======================
// ===================================

SDL_GPUIndexBuffer::SDL_GPUIndexBuffer([[maybe_unused]] const uint32_t* indices, const uint32_t size)
    : m_count(size)
{
}

SDL_GPUIndexBuffer::~SDL_GPUIndexBuffer()
{
}

auto SDL_GPUIndexBuffer::Bind() const -> void
{
}

auto SDL_GPUIndexBuffer::Unbind() const -> void
{
}

auto SDL_GPUIndexBuffer::GetCount() const -> uint32_t
{
    return 0;
}
} // namespace seed