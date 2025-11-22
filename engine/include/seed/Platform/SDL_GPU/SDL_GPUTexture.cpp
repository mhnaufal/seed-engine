#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif

#include <Logger.h>
#include <SDL_GPUTexture.h>

#include <stb_image.h>

namespace seed
{
    SDL_GPUTexture2D::SDL_GPUTexture2D(const std::string& path)
        : m_path(path)
    {
        SEED_PROFILE_FUNCTION();

        int channels{}, width{}, height{};

        stbi_set_flip_vertically_on_load(true);
        const auto data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        m_width = width;
        m_height = height;

        stbi_image_free(data);
    }

    SDL_GPUTexture2D::SDL_GPUTexture2D(const uint32_t width, const uint32_t height)
        : m_width(width), m_height(height)
    {
        SEED_PROFILE_FUNCTION();

    }

    SDL_GPUTexture2D::~SDL_GPUTexture2D()
    {
        SEED_PROFILE_FUNCTION();

    }

    auto SDL_GPUTexture2D::Bind(const uint32_t slot) -> void
    {
        SEED_PROFILE_FUNCTION();

    }

    auto SDL_GPUTexture2D::Unbind(const uint32_t slot) -> void
    {
        SEED_PROFILE_FUNCTION();

    }

    auto SDL_GPUTexture2D::SetData(void* data, const uint32_t size) -> void
    {
        SEED_PROFILE_FUNCTION();

    }
} // namespace seed
