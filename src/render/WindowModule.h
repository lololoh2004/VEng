#pragma once
#include "SDL3/SDL_init.h"

class WindowModule{
private:
    SDL_Window* window;
public:
    bool init();
    [[nodiscard]] SDL_Window* get_window() const noexcept;
    void close() noexcept;
};
