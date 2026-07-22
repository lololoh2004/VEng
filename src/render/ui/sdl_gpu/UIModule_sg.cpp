#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlgpu3.h"
#include "../UIModule.h"
#include "term/term_wrapper.hpp"

bool UIModule::init(SDL_Window* window, void* render_context){
    SDL_GPUDevice* device = static_cast<SDL_GPUDevice*>(render_context);
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui_ImplSDL3_InitForSDLGPU(window);

    ImGui_ImplSDLGPU3_InitInfo init_info = {};
    init_info.Device               = device;
    init_info.ColorTargetFormat    = SDL_GetGPUSwapchainTextureFormat(device, window);
    init_info.MSAASamples          = SDL_GPU_SAMPLECOUNT_1;
    init_info.SwapchainComposition = SDL_GPU_SWAPCHAINCOMPOSITION_SDR;
    init_info.PresentMode          = SDL_GPU_PRESENTMODE_VSYNC;

    if (!ImGui_ImplSDLGPU3_Init(&init_info)) {
        //term::msg("[UI] ERROR : Ну сука сам догадайся еблан");
        term::msg("[UI] ERROR : idk\n");
        return false;
    }
    term::msg("[UI] INFO : The ImGUI service was started successfully\n");
    return true;
}
void UIModule::new_frame(){
    ImGui_ImplSDLGPU3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
}
void UIModule::shutdown(){
    if (ImGui::GetCurrentContext()){
        ImGui_ImplSDL3_Shutdown();
        ImGui_ImplSDLGPU3_Shutdown();
        ImGui::DestroyContext();
        term::msg("[UI] INFO : The ImGUI service was stopped successfully\n");
    } else {
        term::msg("[UI] ERROR : No ImGUI context to shutdown\n");
    }
}
