cmake_minimum_required(VERSION 4.1)
project(VEng)

# Small variables
set(CMAKE_CXX_STANDARD 23)
set(ENG_NAME "Veng")
option(USE_VULKAN "Build engine with Vulkan backend" OFF)

# Put all in root directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}")


# === SDL3 === (STEP_1)
set(SDL_TESTS OFF CACHE BOOL "" FORCE)
set(SDL_EXAMPLES OFF CACHE BOOL "" FORCE)
# SDL3 cmake
add_subdirectory(lib/sdl3)

# === ImGUI === (STEP_1)
# ImGUI include files
set(IMGUI_SRC
        lib/imgui/imgui.cpp
        lib/imgui/imgui_draw.cpp
        lib/imgui/imgui_widgets.cpp
        lib/imgui/imgui_tables.cpp
        lib/imgui/imgui_demo.cpp
        lib/imgui/backends/imgui_impl_sdl3.cpp
        lib/imgui/backends/imgui_impl_sdlgpu3.cpp
        src/utils/math/lerp.hpp
        src/utils/math/abs.h
        src/utils/math/remap.hpp
        src/utils/math/clamp.hpp
        src/utils/math/all_math.h
)


# === MY CODE ===
# Vulkan tumbler
if(USE_VULKAN)
    list(APPEND UI_SOURCES
            #src/render/backends/vulkan/VulkanRenderModule.cpp
            src/render/ui/vulkan/UIModule_vk.cpp
    )
else()
    list(APPEND UI_SOURCES
            #src/render/backends/sdl_gpu/SDLRenderModule.cpp
            src/render/ui/sdl_gpu/UIModule_sg.cpp
    )
endif()

add_executable(${ENG_NAME}
        src/main.cpp
        ${IMGUI_SRC}
        src/term/term_wrapper.hpp
        src/interfaces/IEngine.hpp
        src/interfaces/IEngine_impl.cpp
        src/interfaces/IEngine_impl.h
        src/render/WindowModule.cpp
        src/render/WindowModule.h
        src/render/ui/UIModule.cpp
        src/render/ui/UIModule.h
        ${UI_SOURCES}
        src/render/backend/SDLRenderModule.cpp
        src/render/backend/SDLRenderModule.h
        src/utils/math/approach.hpp
        src/utils/math/neg.h
)

# === MY CODE ===


# === LINKING && DIRECTORIES
# LuaJIT
target_link_directories(${ENG_NAME} PRIVATE
        "lib/luajit/src")
# SDL3 + LuaJIT (Linking libraries to project)
target_link_libraries(${ENG_NAME} PRIVATE
        SDL3::SDL3
        lua51
)
target_include_directories(${ENG_NAME} PRIVATE
        src
        # ImGUI
        lib/imgui
        lib/imgui/backends
        # Sol2
        lib/sol2/include
        # LuaJIT
        lib/luajit/src
        # SDL3
        lib/sdl3/include
)
# LuaJIT (compile settings)
target_compile_definitions(${ENG_NAME} PRIVATE
        SOL_ALL_SAFETIES_ON=1
        SOL_USING_LUAJIT=1
        LUA_BUILD_AS_DLL=1
)


# === SMALL ADDITIONS ===
if(WIN32 AND CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    get_filename_component(MINGW_BIN_DIR ${CMAKE_CXX_COMPILER} DIRECTORY)
    set(GCC_DLLS
            "${MINGW_BIN_DIR}/libstdc++-6.dll"
            "${MINGW_BIN_DIR}/libgcc_s_seh-1.dll"
            "${MINGW_BIN_DIR}/libwinpthread-1.dll"
    )

    add_custom_command(TARGET ${ENG_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${GCC_DLLS}
            $<TARGET_FILE_DIR:${ENG_NAME}>
    )
endif()