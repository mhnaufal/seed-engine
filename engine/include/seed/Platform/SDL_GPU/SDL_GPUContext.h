#pragma once

#include <Renderer/GraphicsContext.h>

#include <SDL3/SDL_gpu.h>
#include <SDL3/SDL_video.h>

namespace seed
{
    class SDL_GPUContext final : public GraphicsContext
    {
    public:
        explicit SDL_GPUContext(SDL_Window* window_handle);
        ~SDL_GPUContext() override;

        auto Init() -> void override;
        auto SwapBuffers() -> void override;
        auto Shutdown() -> void override;

        [[nodiscard]] auto GetDevice() const -> SDL_GPUDevice* { return m_gpu_device; };
        [[nodiscard]] auto GetCommandBuffer() const -> SDL_GPUCommandBuffer* { return m_command_buffer; };
        [[nodiscard]] auto GetSwapchainTexture() const -> SDL_GPUTexture* { return m_gpu_swapchain_texture; };

    private:
        auto InitPhysicalDevice() -> bool;

    private:
        SDL_Window* m_window_handle{};
        SDL_GPUDevice* m_gpu_device{};
        SDL_GPUCommandBuffer* m_command_buffer{};
        SDL_GPUTexture* m_gpu_swapchain_texture{};

        SDL_GPUBufferCreateInfo m_buffer_info{};
        SDL_GPUGraphicsPipeline* m_graphic_pipeline{};
        SDL_GPUShader* m_vertex_shader{};
        SDL_GPUShader* m_fragment_shader{};
        // SDL_GPUTransferBufferCreateInfo m_transfer_buffer_info{};
        // SDL_GPUTransferBuffer* m_transfer_buffer{};
        // SDL_GPUCopyPass* m_copy_pass{};
        // SDL_GPUTransferBufferLocation m_location{};
        // SDL_GPUBufferRegion m_region{};
    };
} // namespace seed
