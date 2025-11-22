#include <SDL_GPUContext.h>
#include <Debug/Instrumentor.h>

#include <Logger.h>
#include <SDL3/SDL.h>

namespace seed
{
    SDL_GPUContext::SDL_GPUContext(SDL_Window* window_handle)
        : m_window_handle(window_handle)
    {
        SEED_PROFILE_FUNCTION();

    }

    SDL_GPUContext::~SDL_GPUContext()
    {
        SEED_PROFILE_FUNCTION();

    }

    void SDL_GPUContext::Shutdown()
    {
        SEED_PROFILE_FUNCTION();

        SEED_LOG_INFO("Destroying SDL GPU context...");
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

        uint32_t width, height;
        const bool is_success = SDL_WaitAndAcquireGPUSwapchainTexture(
            m_command_buffer,
            m_window_handle,
            &m_gpu_swapchain_texture,
            &width,
            &height);
        if (!is_success || m_gpu_swapchain_texture == nullptr)
        {
            SEED_LOG_ERROR("Failed to Acquire GPU Swapchain");
            return;
        }

        if (m_gpu_swapchain_texture != nullptr)
        {
            SDL_GPUColorTargetInfo color_target_info{};
            color_target_info.clear_color = {0.46f, 0.27f, 0.84f, 1.0f};
            color_target_info.load_op = SDL_GPU_LOADOP_CLEAR;
            color_target_info.store_op = SDL_GPU_STOREOP_STORE;
            color_target_info.texture = m_gpu_swapchain_texture;
            color_target_info.cycle = true;

            SDL_GPURenderPass* render_pass = SDL_BeginGPURenderPass(m_command_buffer, &color_target_info, 1, nullptr);
            SDL_EndGPURenderPass(render_pass);
            SDL_SubmitGPUCommandBuffer(m_command_buffer);
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

        return true;
    }
} // namespace seed
