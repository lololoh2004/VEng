#include "WindowModule.h"

#include "term/term_wrapper.hpp"

bool WindowModule::init(){
    if (!SDL_InitSubSystem(SDL_INIT_VIDEO)){
        term::msg("[RENDER] ERROR : SDL_video initialization failed\n");
        return false;
    }
    window = SDL_CreateWindow(
    "Engine_Debug_Window",
    600, 480,
    SDL_WINDOW_RESIZABLE
    );
    if (!window){
        term::msg("[RENDER] ERROR : SDL_CreateWindow failed\n");
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
        return false;
    }
    term::msg("[RENDER] INFO : SDL configuration was successful\n");
    return true;
}
[[nodiscard]] SDL_Window* WindowModule::get_window() const noexcept{
    return window;
}
void WindowModule::close() noexcept{
    if (window){
        SDL_DestroyWindow(window);
        window = nullptr;
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
        term::msg("[RENDER] INFO : SDL was successfully unloaded\n");
    }
    term::msg("[RENDER] ERROR : No window to close\n");
}