#include <seed/seed.h>
#include <seed/Platform/OpenGL/OpenGLShader.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>

class GameLayer : public seed::Layer {
public:
    GameLayer()
        : seed::Layer("GameLayer")
        , m_camera(-1.6f, 1.6f, -0.9f, 0.9f)
        , m_camera_position(0.0f)
    {
        seed::Renderer::SetRendererAPI(seed::RendererAPI::API::OPENGL);
        seed::Renderer::Init();

        //* Triangle Shape
        constexpr float shape_vertices[3 * 7] = {
        -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
        0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
        0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
        };

        //* Square Shape
        constexpr float texture_shape_vertices[5 * 4] = {
            -0.8f, -0.8f, 0.0f, 0.0f, 0.0f,
            0.8f, -0.8f, 0.0f, 1.0f, 0.0f,
            0.8f,  0.8f, 0.0f, 1.0f, 1.0f,
			-0.8f,  0.8f, 0.0f, 0.0f, 1.0f
        };

        //* Triangle
        m_triangle_vertex_buffer = seed::VertexBuffer::Create(shape_vertices, sizeof(shape_vertices));
        const seed::BufferLayout triangle_layout({
            {seed::ShaderDataType::FLOAT3, std::string("attribute_position")},
            {seed::ShaderDataType::FLOAT4, std::string("attribute_color")},
        });
        m_triangle_vertex_buffer->SetLayout(triangle_layout);

        //* Texture
        m_texture_vertex_buffer = seed::VertexBuffer::Create(texture_shape_vertices, sizeof(texture_shape_vertices));
        const seed::BufferLayout texture_layout({
            {seed::ShaderDataType::FLOAT3, std::string("attribute_position")},
            {seed::ShaderDataType::FLOAT2, std::string("attribute_texture")}
        });
        m_texture_vertex_buffer->SetLayout(texture_layout);

        //* Triangle
        m_triangle_vertex_array = seed::VertexArray::Create();
        m_triangle_vertex_array->AddVertexBuffer(m_triangle_vertex_buffer);

        //* Texture
        m_texture_vertex_array = seed::VertexArray::Create();
        m_texture_vertex_array->AddVertexBuffer(m_texture_vertex_buffer);

        //* Triangle
        constexpr uint32_t triangle_indices[3] = {0, 1, 2};
        m_triangle_index_buffer = seed::IndexBuffer::Create(triangle_indices, sizeof(triangle_indices) / sizeof(uint32_t));
        m_triangle_vertex_array->SetIndexBuffer(m_triangle_index_buffer);

        //* Texture
        constexpr uint32_t texture_indices[6] = {0, 1, 2, 2, 3, 0};
        m_texture_index_buffer = seed::IndexBuffer::Create(texture_indices, sizeof(texture_indices) / sizeof(uint32_t));
        m_texture_vertex_array->SetIndexBuffer(m_texture_index_buffer);

        //* Triangle Shader
        std::string vertex_code = R"(
        #version 460 core

        layout(location = 0) in vec3 attribute_position;
        layout(location = 1) in vec4 attribute_color;

        uniform mat4 uniform_view_projection;
        uniform mat4 uniform_transform;

        out vec3 output_position;
        out vec4 output_color;

        void main()
        {
            output_position = attribute_position;
            output_color = attribute_color;
            gl_Position = uniform_view_projection * uniform_transform * vec4(attribute_position, 1.0);
        }
        )";

        std::string fragment_code = R"(
        #version 460 core

        layout(location = 0) out vec4 color;

        in vec3 output_position;
        in vec4 output_color;

        uniform vec3 uniform_color;

        void main()
        {
            // Clamp (-1, +1) into (0, +1)
            // color = vec4((output_position + 1) / 2, 1.0);
            // color = output_color;
            color = vec4(uniform_color, 1.0);
        }
        )";

        m_triangle_shader = seed::Shader::Create("TriangleShader", vertex_code.c_str(), fragment_code.c_str());

        //* Texture Shader
        // m_texture_shader = seed::Shader::Create("assets/shaders/texture.glsl");
        auto m_texture_shader = m_shader_lib_object.Load("assets/shaders/texture.glsl");

        m_texture2D = seed::Texture2D::Create("assets/back.jpg");
        std::dynamic_pointer_cast<seed::OpenGLShader>(m_texture_shader)->Bind();
        std::dynamic_pointer_cast<seed::OpenGLShader>(m_texture_shader)->UploadUniformInt("uniform_texture", 0);

        m_audio = std::make_shared<seed::Audio>(m_sound_path);
        m_audio->Play();
    }

    ~GameLayer()
    {
        m_texture2D->Unbind();

        m_texture_vertex_array->Unbind();
        m_texture_vertex_buffer->Unbind();
        // m_texture_shader->Unbind();

        m_triangle_vertex_array->Unbind();
        m_triangle_vertex_buffer->Unbind();
        m_triangle_shader->Unbind();
    }

    auto OnUpdate([[maybe_unused]] seed::Timestep& time_step) -> void override
    {
        if (seed::Input::IsKeyPressed(SDL_SCANCODE_A)) {
            m_camera_position.x = m_camera_position.x + (m_camera_move_speed * time_step);
        }
        else if (seed::Input::IsKeyPressed(SDL_SCANCODE_D)) {
            m_camera_position.x = m_camera_position.x - (m_camera_move_speed * time_step);
        }

        if (seed::Input::IsKeyPressed(SDL_SCANCODE_W)) {
            m_camera_position.y = m_camera_position.y - (m_camera_move_speed * time_step);
        }
        else if (seed::Input::IsKeyPressed(SDL_SCANCODE_S)) {
            m_camera_position.y = m_camera_position.y + (m_camera_move_speed * time_step);
        }

        if (seed::Input::IsKeyPressed(SDL_SCANCODE_Q)) {
            m_camera_rotation = m_camera_rotation - (m_camera_rotation_speed * time_step);
        }
        else if (seed::Input::IsKeyPressed(SDL_SCANCODE_E)) {
            m_camera_rotation = m_camera_rotation + (m_camera_rotation_speed * time_step);
        }

        glm::vec4 clear_color((249.0f / 255.0f), (155.0f / 255.0f), (254.0f / 255.0f), 1.00f);
        seed::RenderCommand::SetClearColor(clear_color);
        seed::RenderCommand::Clear();

        m_camera.SetPosition(m_camera_position);
        m_camera.SetRotation(m_camera_rotation);

        seed::Renderer::BeginScene(m_camera);

        glm::mat4 transform(1.0f);
        if (seed::Input::IsKeyPressed(SDL_SCANCODE_C)) {
            transform = glm::scale(glm::mat4(0.5f), glm::vec3(0.5f));
        }

        //* Triangle
        std::dynamic_pointer_cast<seed::OpenGLShader>(m_triangle_shader)->Bind();
        std::dynamic_pointer_cast<seed::OpenGLShader>(m_triangle_shader)->UploadUniformFloat3("uniform_color", m_selected_color);
        seed::Renderer::Submit(m_triangle_shader, m_triangle_vertex_array, transform);

        //* Texture
        auto m_texture_shader = m_shader_lib_object.Get("texture");
        m_texture2D->Bind();
        std::dynamic_pointer_cast<seed::OpenGLShader>(m_texture_shader)->Bind();
        seed::Renderer::Submit(m_texture_shader, m_texture_vertex_array, transform);

        seed::Renderer::EndScene();
    }

    auto OnEvent([[maybe_unused]] seed::Event& event) -> void override {}

    auto OnImGuiRender([[maybe_unused]] const float fps) -> void override {
        ImGui::Begin("Settings");
		ImGui::ColorEdit3("Color Picker", glm::value_ptr(m_selected_color));
		ImGui::End();
    }

private:
    seed::OrthographicCamera m_camera;

    seed::Ref<seed::Shader> m_triangle_shader = nullptr;
    seed::Ref<seed::VertexArray> m_triangle_vertex_array = nullptr;
    seed::Ref<seed::VertexBuffer> m_triangle_vertex_buffer = nullptr;
    seed::Ref<seed::IndexBuffer> m_triangle_index_buffer = nullptr;

    seed::ShaderLibrary m_shader_lib_object{};
    // seed::Ref<seed::Shader> m_texture_shader = nullptr;
    seed::Ref<seed::VertexArray> m_texture_vertex_array = nullptr;
    seed::Ref<seed::VertexBuffer> m_texture_vertex_buffer = nullptr;
    seed::Ref<seed::IndexBuffer> m_texture_index_buffer = nullptr;

    seed::Ref<seed::Texture2D> m_texture2D = nullptr;

    glm::vec3 m_camera_position{};
	float m_camera_move_speed = 1.0f;

	float m_camera_rotation = 0.0f;
	float m_camera_rotation_speed = 45.0f;

    seed::Ref<seed::Audio> m_audio = nullptr;
    std::string m_sound_path = "assets/selow.mp3";

    glm::vec3 m_selected_color = { 0.2f, 0.3f, 0.8f };
};

class GameApplication : public seed::Application {
public:
    GameApplication()
    {
        m_game_layer = new GameLayer();
        PushLayer(m_game_layer);
    }

    ~GameApplication()
    {
        PopLayer(m_game_layer);
        delete m_game_layer;
    }

private:
    seed::Layer* m_game_layer{};
};

seed::Application* CreateApplication()
{
    return new GameApplication();
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char** __argv)
{
    auto game = CreateApplication();
    game->run();
    delete game;

    return 0;
}
