#include <iostream>
#include <SDL_GPUContext.h>
#include <Debug/Instrumentor.h>

#include <Logger.h>
#include <SDL3/SDL.h>
#include <Utils/Utils.h>

namespace seed
{
    SDL_GPUContext::SDL_GPUContext(SDL_Window* window_handle)
        : m_window_handle(window_handle)
    {
        SEED_PROFILE_FUNCTION();
    }

    SDL_GPUContext::~SDL_GPUContext()
    = default;

    void SDL_GPUContext::Shutdown()
    {
        SEED_PROFILE_FUNCTION();

        SEED_LOG_INFO("Destroying SDL GPU context...");
        SDL_ReleaseGPUGraphicsPipeline(m_device, m_graphic_pipeline);
        SDL_ReleaseGPUShader(m_device, m_vertex_shader);
        SDL_ReleaseGPUShader(m_device, m_fragment_shader);

        // SDL_ReleaseGPUBuffer(m_device, m_gpu_vertex_buffer);
        // SDL_ReleaseGPUTransferBuffer(m_device, m_transfer_buffer);

        SDL_ReleaseWindowFromGPUDevice(m_device, m_window_handle);
        SDL_DestroyGPUDevice(m_device);
    }

    auto SDL_GPUContext::Init() -> void
    {
        SEED_PROFILE_FUNCTION();

        SEED_LOG_INFO("Initializing SDL GPU context...");

        bool is_success = InitPhysicalDevice();
        if (!is_success)
        {
            SEED_LOG_FATAL_ERROR("Failed to Get Physical Device!");
        }
    }

    auto SDL_GPUContext::SwapBuffers() -> void
    {
        SEED_PROFILE_FUNCTION();

        m_command_buffer = SDL_AcquireGPUCommandBuffer(m_device);
        if (m_command_buffer == nullptr)
        {
            SEED_LOG_ERROR("Failed to Acquire Command Buffer");
            return;
        }

        // TODO: kalau minimize jangan call ini
        bool is_success = SDL_WaitAndAcquireGPUSwapchainTexture(
            m_command_buffer,
            m_window_handle,
            &m_gpu_swapchain_texture,
            nullptr,
            nullptr);
        if (!is_success || m_gpu_swapchain_texture == nullptr)
        {
            SEED_LOG_ERROR("Failed to Acquire GPU Swapchain");
            return;
        }

        // TODO: TEMP
        if (m_gpu_swapchain_texture != nullptr)
        {
            SDL_GPUColorTargetInfo color_target_info{};
            color_target_info.clear_color = {0.76f, 0.37f, 0.54f, 1.0f};
            color_target_info.load_op = SDL_GPU_LOADOP_CLEAR;
            color_target_info.store_op = SDL_GPU_STOREOP_STORE;
            color_target_info.texture = m_gpu_swapchain_texture;
            // color_target_info.cycle = true;

            SDL_GPURenderPass* render_pass = SDL_BeginGPURenderPass(m_command_buffer, &color_target_info, 1, nullptr);
            SDL_BindGPUGraphicsPipeline(render_pass, m_graphic_pipeline);
            SDL_DrawGPUPrimitives(render_pass, 3, 1, 0, 0);
            SDL_EndGPURenderPass(render_pass);
        }

        is_success &= SDL_SubmitGPUCommandBuffer(m_command_buffer);
        if (!is_success)
        {
            SEED_LOG_ERROR("Failed to Submit Command Buffer!");
            return;
        }
    }

    auto SDL_GPUContext::InitPhysicalDevice() -> bool
    {
        m_device = SDL_CreateGPUDevice(SDL_GPU_SHADERFORMAT_SPIRV, true, nullptr);
        if (m_device == nullptr)
        {
            SEED_LOG_ERROR("Failed to Create GPU Device context");
            return false;
        }

        bool is_success = SDL_ClaimWindowForGPUDevice(m_device, m_window_handle);
        if (!is_success)
        {
            SEED_LOG_ERROR("Failed to Claim GPU Device context");
            return false;
        }

        // TODO: TEMP
        const std::filesystem::path vertex_shader_file("assets/shaders/triangle.vert.spirv");
        auto vertex_shader_byte = read_shader_file(vertex_shader_file);
        auto vertex_shader_create_info = SDL_GPUShaderCreateInfo();
        vertex_shader_create_info.code_size = vertex_shader_byte.size();
        vertex_shader_create_info.code = vertex_shader_byte.data();
        vertex_shader_create_info.entrypoint = "main";
        vertex_shader_create_info.format = SDL_GPU_SHADERFORMAT_SPIRV;
        vertex_shader_create_info.stage = SDL_GPU_SHADERSTAGE_VERTEX;
        m_vertex_shader = SDL_CreateGPUShader(m_device, &vertex_shader_create_info);

        const std::filesystem::path fragment_shader_file("assets/shaders/triangle.frag.spirv");
        auto fragment_shader_byte = read_shader_file(fragment_shader_file);
        auto fragment_shader_create_info = SDL_GPUShaderCreateInfo();
        fragment_shader_create_info.code_size = fragment_shader_byte.size();
        fragment_shader_create_info.code = fragment_shader_byte.data();
        fragment_shader_create_info.entrypoint = "main";
        fragment_shader_create_info.format = SDL_GPU_SHADERFORMAT_SPIRV;
        fragment_shader_create_info.stage = SDL_GPU_SHADERSTAGE_FRAGMENT;
        m_fragment_shader = SDL_CreateGPUShader(m_device, &fragment_shader_create_info);

        auto color_target_desc = SDL_GPUColorTargetDescription{};
        color_target_desc.format = SDL_GetGPUSwapchainTextureFormat(m_device, m_window_handle);

        SDL_GPUGraphicsPipelineTargetInfo pipeline_target_info{};
        pipeline_target_info.num_color_targets = 1;
        pipeline_target_info.color_target_descriptions = &color_target_desc;

        SDL_GPUGraphicsPipelineCreateInfo pipeline_create_info{};
        pipeline_create_info.vertex_shader = m_vertex_shader;
        pipeline_create_info.fragment_shader = m_fragment_shader;
        pipeline_create_info.primitive_type = SDL_GPU_PRIMITIVETYPE_TRIANGLELIST;
        pipeline_create_info.target_info = pipeline_target_info;

        m_graphic_pipeline = SDL_CreateGPUGraphicsPipeline(m_device, &pipeline_create_info);

        return true;
    }
} // namespace seed
