#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#define STB_IMAGE_IMPLEMENTATION

#include <Logger.h>
#include <OpenGLTexture.h>

#include <stb_image.h>

namespace seed {
OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
    : m_path(path)
{
    int channels{}, width{}, height{};

    stbi_set_flip_vertically_on_load(true);
    const auto data = stbi_load(path.c_str(), &width, &height, &channels, 0);
    m_width = width;
    m_height = height;

    if (channels == 4) {
        m_internal_format = GL_RGBA8;
        m_data_format = GL_RGBA;
    }
    else if (channels == 3) {
        m_internal_format = GL_RGB8;
        m_data_format = GL_RGB;
    }

    glCreateTextures(GL_TEXTURE_2D, 1, &m_renderer_id);
    glTextureStorage2D(m_renderer_id, 1, m_internal_format, static_cast<int>(m_width), static_cast<int>(m_height));

    glTextureParameteri(m_renderer_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(m_renderer_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTextureParameteri(m_renderer_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(m_renderer_id, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTextureSubImage2D(
        m_renderer_id,
        0,
        0,
        0,
        m_width,
        m_height,
        m_data_format,
        GL_UNSIGNED_BYTE,
        data);

    stbi_image_free(data);
}

OpenGLTexture2D::OpenGLTexture2D(const uint32_t width, const uint32_t height)
    : m_width(width), m_height(height)
{
    m_internal_format = GL_RGBA8;
    m_data_format = GL_RGBA;

    glCreateTextures(GL_TEXTURE_2D, 1, &m_renderer_id);
    glTextureStorage2D(m_renderer_id, 1, m_internal_format, static_cast<int>(m_width), static_cast<int>(m_height));

    glTextureParameteri(m_renderer_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(m_renderer_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTextureParameteri(m_renderer_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(m_renderer_id, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

OpenGLTexture2D::~OpenGLTexture2D()
{
    glDeleteTextures(1, &m_renderer_id);
}

auto OpenGLTexture2D::Bind(const uint32_t slot) -> void
{
    glBindTextureUnit(slot, m_renderer_id);
}

auto OpenGLTexture2D::Unbind(const uint32_t slot) -> void
{
    glBindTextureUnit(slot, 0);
}

auto OpenGLTexture2D::SetData(void* data, const uint32_t size) -> void
{
    const uint32_t byte_per_pixel = m_data_format == GL_RGBA ? 4 : 3;
    if (size != m_width * m_height * byte_per_pixel) {
        SEED_LOG_ERROR("Invalid texture data size!");
        return;
    }

    glTextureSubImage2D(
        m_renderer_id,
        0,
        0,
        0,
        static_cast<int>(m_width),
        static_cast<int>(m_height),
        m_data_format,
        GL_UNSIGNED_BYTE,
        data);
}
} // namespace seed