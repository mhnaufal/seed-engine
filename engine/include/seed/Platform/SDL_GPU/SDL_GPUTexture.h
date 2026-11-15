#pragma once

#include "SDL_GPUShader.h"
#include "Texture.h"

// #include <glad.h>

namespace seed
{
    class SDL_GPUTexture2D final : public Texture2D
    {
    public:
        explicit SDL_GPUTexture2D(const std::string& path);
        explicit SDL_GPUTexture2D(uint32_t width, uint32_t height);
        ~SDL_GPUTexture2D() override;

        auto GetWidth() -> uint32_t const override { return m_width; };
        auto GetHeight() -> uint32_t const override { return m_height; }

        auto Bind(uint32_t slot) -> void override;
        auto Unbind(uint32_t slot) -> void override;

        auto SetData(void* data, uint32_t size) -> void override;

    private:
        std::string m_path{};
        uint32_t m_renderer_id{};
        uint32_t m_width{};
        uint32_t m_height{};
        GLenum m_internal_format{}, m_data_format{};
    };
} // namespace seed
