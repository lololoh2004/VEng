#pragma once
#include "SDL3/SDL_gpu.h"

class SDLRenderModule{
private:
    SDL_GPUDevice* device = nullptr;
public:
    bool init(SDL_Window* window);
    SDL_GPUDevice* get_device() const noexcept { return device; }
    void update(SDL_Window* window);
};
