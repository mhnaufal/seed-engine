#pragma once

#include <Renderer/Buffer.h>

namespace seed {
class SDL_GPUVertexBuffer final : public VertexBuffer {
public:
    SDL_GPUVertexBuffer(const float* vertices, uint32_t size);
    ~SDL_GPUVertexBuffer() override;

    auto Bind() const -> void override;
    auto Unbind() const -> void override;

private:
    uint32_t m_renderer_id{};
};

class SDL_GPUIndexBuffer final : public IndexBuffer {
public:
    SDL_GPUIndexBuffer(const uint32_t* indices, const uint32_t size);
    ~SDL_GPUIndexBuffer() override;

    auto Bind() const -> void override;
    auto Unbind() const -> void override;
    auto GetCount() const -> uint32_t override;

private:
    uint32_t m_renderer_id{};
    uint32_t m_count{};
};
} // namespace seed