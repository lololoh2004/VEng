#include "IEngine_impl.h"

#include "imgui_impl_sdl3.h"
#include "SDL3/SDL_timer.h"
#include "term/term_wrapper.hpp"
#include "render/backend/SDLRenderModule.h"

int IEngine_impl::init(int argc, char* argv[]){
    term::msg("[SYS] INFO : Enter WindowModule initialization\n");
    if (!window.init()) return -1;
    term::msg("\n");

    term::msg("[SYS] INFO : Saving window to cache\n");
    cached_window = window.get_window();
    term::msg("[SYS] INFO : Creating an render class\n");
    render = std::make_unique<SDLRenderModule>(cached_window);
    // it can be different (BUT only from RenderModule interface) | example: VKRenderModule
    term::msg("\n");

    term::msg("[SYS] INFO : Enter Render initialization\n");
    if (!render->init()) return -2;
    term::msg("[SYS] INFO : Conversion of SDLRenderModule from the RenderModule interface\n");
    auto* sdl_render = dynamic_cast<SDLRenderModule*>(render.get());
    // it can be different (BUT only from RenderModule interface) | example: VKRenderModule

    term::msg("[SYS] INFO : Check on SDLRender..");
    if (sdl_render != nullptr) {
        term::msg("TRUE\n");
        SDL_GPUDevice* gpu_device = sdl_render->get_device();
        term::msg("[SYS] INFO : Enter UI initialization\n");
        if (!ui.init(cached_window, gpu_device)) return -3;
    }
    term::msg("\n");

    term::msg("[SYS] INFO : Enter Lua initialization\n");
    if (!lua::init()) return -4;
    term::msg("\n");

    running = true;
    return 0;
}
void IEngine_impl::run(){
    bool missing_flag = lua::run<bool, lua::RunMode::Secure, 2>("test_bounds.lua");
    term::msg("log: ", missing_flag);

    SDL_Event event;
    while (running){
        while (SDL_PollEvent(&event)){
            ImGui_ImplSDL3_ProcessEvent(&event);
            if (event.type == SDL_EVENT_QUIT)
                running = false;
        }
        ui.new_frame();
        ImGui::ShowDemoWindow();
        ImGui::Render();

        render->update();
        // render->begin_render();
        // render->end_render();

        SDL_Delay(1);
    }
}
void IEngine_impl::shutdown(){
    term::msg("[SYS] Shutting down..");
    ui.shutdown();
    window.close();
    //script.shutdown();

    SDL_Quit();
    term::msg("[SYS] Bye.\n");
}
