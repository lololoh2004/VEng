#include "IEngine_impl.h"

#include "imgui_impl_sdl3.h"
#include "SDL3/SDL_timer.h"
#include "sol/stack.hpp"
#include "term/term_wrapper.hpp"

int IEngine_impl::init(int argc, char* argv[]){
    if (!window.init())
        return -1;
    if (!render.init(window.get_window()))
        return -2;
    if (!ui.init(window.get_window(), render.get_device()))
        return -3;
    // if (!script.lua_init())
    //     return -4;
    running = true;
    return 0;
}
void IEngine_impl::run(){
    //term::msg("placeholder for 'run'\n");
    SDL_Event event;
    auto* cached_window = window.get_window();
    while (running){
        while (SDL_PollEvent(&event)){
            ImGui_ImplSDL3_ProcessEvent(&event);
            if (event.type == SDL_EVENT_QUIT)
                running = false;
            SDL_Delay(1);
        }
        ui.render();
        render.update(cached_window);
    }
}
void IEngine_impl::shutdown(){
    term::msg("[SYS] Shutting down..");
    // term::msg("placeholder for 'shutdown'\n");
    ui.shutdown();
    window.close();
    //script.shutdown();

    SDL_Quit();
    term::msg("[SYS] Bye.\n");
}
