#include "SDLRenderModule.h"

#include "imgui_impl_sdlgpu3.h"
#include "term/term_wrapper.hpp"

bool SDLRenderModule::init(){
    device = SDL_CreateGPUDevice(
        SDL_GPU_SHADERFORMAT_SPIRV | SDL_GPU_SHADERFORMAT_DXBC,
        true,
        nullptr
        );
    if(!device){
        term::msg("[RENDER] ERROR : Failed to initialize your device and drivers\n");
        return false;
    }
    if (!SDL_ClaimWindowForGPUDevice(device, window)){
        SDL_DestroyGPUDevice(device);
        term::msg("[RENDER] ERROR : Failed to claim SDL GPU device\n");
        return false;
    }
    term::msg("[RENDER] INFO : SDL render initialization successful\n");
    return true;
}
void SDLRenderModule::begin_render() {
    if (!device || !window) return;

    cmd_buffer = SDL_AcquireGPUCommandBuffer(device);
    if (!cmd_buffer) return;

    swapchain_texture = nullptr;
    SDL_AcquireGPUSwapchainTexture(cmd_buffer, window, &swapchain_texture, nullptr, nullptr);
}
void SDLRenderModule::end_render() {
    if (!cmd_buffer) return;

    if (swapchain_texture != nullptr) {
        ImGui_ImplSDLGPU3_PrepareDrawData(ImGui::GetDrawData(), cmd_buffer);

        SDL_GPUColorTargetInfo color_targets = {};
        color_targets.texture     = swapchain_texture;
        color_targets.clear_color = SDL_FColor{ 0.1f, 0.1f, 0.1f, 1.0f };
        color_targets.load_op     = SDL_GPU_LOADOP_CLEAR;
        color_targets.store_op    = SDL_GPU_STOREOP_STORE;

        SDL_GPURenderPass* render_pass = SDL_BeginGPURenderPass(cmd_buffer, &color_targets, 1, nullptr);

        if (render_pass != nullptr) {
            ImGui_ImplSDLGPU3_RenderDrawData(ImGui::GetDrawData(), cmd_buffer, render_pass);

            SDL_EndGPURenderPass(render_pass);
        }
    }

    SDL_SubmitGPUCommandBuffer(cmd_buffer);

    cmd_buffer = nullptr;
    swapchain_texture = nullptr;
}
void SDLRenderModule::shutdown(){
    if (device){
        SDL_DestroyGPUDevice(device);
        device = nullptr;
    }
    term::msg("[RENDER] INFO : SDL renderer removal successful\n");
}