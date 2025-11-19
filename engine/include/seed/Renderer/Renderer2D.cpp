#include "Logger.h"

#include <Buffer.h>
#include <RenderCommand.h>
#include <Shader.h>
#include <Texture.h>
#include <OrthographicCamera.h>
#include <VertexArray.h>
#include <Renderer2D.h>

#include <glm/ext/matrix_transform.hpp>

namespace seed {
struct Renderer2DState {
    Ref<VertexArray> quad_vertex_array{};
    // Ref<Shader> quad_shader{};
    Ref<Shader> texture_shader{};
    Ref<Texture2D> default_texture{};
};

static Renderer2DState* state;

auto Renderer2D::Init() -> void
{
    state = new Renderer2DState;
    state->quad_vertex_array = VertexArray::Create();

    constexpr float square_vertices[5 * 4] = {
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f
    };

    Ref<VertexBuffer> square_vertex_buffer{};
    square_vertex_buffer = VertexBuffer::Create(square_vertices, sizeof(square_vertices));
    square_vertex_buffer->SetLayout(
    {
        {ShaderDataType::FLOAT3, "attribute_position"},
        {ShaderDataType::FLOAT2, "attribute_texture"}
    });
    state->quad_vertex_array->AddVertexBuffer(square_vertex_buffer);

    constexpr uint32_t square_indices[6] = {0, 1, 2, 2, 3, 0};
    Ref<IndexBuffer> square_index_buffer{};
    square_index_buffer = IndexBuffer::Create(square_indices, sizeof(square_indices));
    state->quad_vertex_array->SetIndexBuffer(square_index_buffer);

    state->default_texture = Texture2D::Create(1, 1);
    uint32_t white_texture = 0xffffffff;
    state->default_texture->SetData(&white_texture, sizeof(uint32_t));

    // state->quad_shader = Shader::Create("assets/shaders/quad_colored.glsl");

    state->texture_shader = Shader::Create("assets/shaders/texture.glsl");
    state->texture_shader->Bind();
    state->texture_shader->SetUniformInt("uniform_texture", 0);
}

auto Renderer2D::Shutdown() -> void
{
    delete state;
}

auto Renderer2D::BeginScene(const OrthographicCamera& camera) -> void
{
    // state->quad_shader->Bind();
    // state->quad_shader->SetUniformMat4("uniform_view_projection", camera.GetViewProjectionMatrix());

    state->texture_shader->Bind();
    state->texture_shader->SetUniformMat4("uniform_view_projection", camera.GetViewProjectionMatrix());
}

auto Renderer2D::EndScene() -> void
{
    // state->quad_shader->Unbind();
    state->texture_shader->Unbind();
}

void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
{
    DrawQuad({position.x, position.y, 0.0f}, size, color);
}

void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
{
    // state->quad_shader->Bind();
    // state->quad_shader->SetUniformFloat4("uniform_color", color);
    state->texture_shader->SetUniformFloat4("uniform_color", color);
    state->default_texture->Bind(0);

    const glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
                                glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f)) *
                                glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
    // state->quad_shader->SetUniformMat4("uniform_transform", transform);
    state->texture_shader->SetUniformMat4("uniform_transform", transform);

    state->quad_vertex_array->Bind();
    RenderCommand::DrawIndexed(state->quad_vertex_array);
}

void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture)
{
    DrawQuad({position.x, position.y, 0.0f}, size, texture);
}

void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture)
{
    state->texture_shader->SetUniformFloat4("uniform_color", glm::vec4(1.0f));
    // state->texture_shader->Bind();
    texture->Bind(0);

    const glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
                                // glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f)) *
                                glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
    state->texture_shader->SetUniformMat4("uniform_transform", transform);

    state->quad_vertex_array->Bind();
    RenderCommand::DrawIndexed(state->quad_vertex_array);
}
}