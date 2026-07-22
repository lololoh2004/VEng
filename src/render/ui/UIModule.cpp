#include "UIModule.h"

#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlgpu3.h"

void UIModule::render(){
    // Test logic (ill replace it later with the callback invocation logic)
    new_frame();
    //ImGui::NewFrame(); now in new_frame()
    ImGui::ShowDemoWindow();
    ImGui::Render();
}


