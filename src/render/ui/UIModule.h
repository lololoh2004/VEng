#pragma once
#include "SDL3/SDL_video.h"

class UIModule{
public:
    bool init(SDL_Window* window, void* render_context);
    void shutdown();
    void new_frame();
    void render();
};
