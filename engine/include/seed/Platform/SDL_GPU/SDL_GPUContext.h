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

        [[nodiscard]] auto GetDevice() const -> SDL_GPUDevice* { return m_device; };
        [[nodiscard]] auto GetCommandBuffer() const -> SDL_GPUCommandBuffer* { return m_command_buffer; };

    private:
        auto InitPhysicalDevice() -> bool;

    private:
        SDL_Window* m_window_handle{};
        SDL_GPUDevice* m_device{};
        SDL_GPUCommandBuffer* m_command_buffer{};
        SDL_GPUTexture* m_gpu_swapchain_texture{};
    };
} // namespace seed
