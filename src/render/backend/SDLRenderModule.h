#pragma once
#include "IRenderModule.h"
#include "SDL3/SDL_gpu.h"

class SDLRenderModule : public IRenderModule{
private:
    SDL_Window* window;
    SDL_GPUDevice* device = nullptr;

    [[]] SDL_GPUCommandBuffer* cmd_buffer;
    [[]] SDL_GPUTexture* swapchain_texture;
public:
    explicit SDLRenderModule(SDL_Window* input_window)
        : window(input_window) {}

    [[nodiscard]] SDL_GPUDevice* get_device() const noexcept { return device; }

    bool init()         override;
    void update()       override;
    void shutdown()     override;
};
