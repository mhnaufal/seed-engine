#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#define STB_IMAGE_IMPLEMENTATION

#include <OpenGLTexture.h>

#include <stb_image.h>
#include <glad.h>

namespace seed {
OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
    : m_path(path)
{
    int channels{}, width{}, height{};

    stbi_set_flip_vertically_on_load(true);
    const auto data = stbi_load(path.c_str(), &width, &height, &channels, 0);
    m_width = width;
    m_height = height;

    GLenum internal_format{}, data_format{};

    if (channels == 4) {
        internal_format = GL_RGBA8;
        data_format = GL_RGBA;
    } else if (channels == 3) {
        internal_format = GL_RGB8;
        data_format = GL_RGB;
    }

    glCreateTextures(GL_TEXTURE_2D, 1, &m_renderer_id);
    glTextureStorage2D(m_renderer_id, 1, internal_format, m_width, m_height);

    glTextureParameteri(m_renderer_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(m_renderer_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTextureSubImage2D(m_renderer_id, 0, 0, 0, m_width, m_height, data_format, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
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
} // namespace seed