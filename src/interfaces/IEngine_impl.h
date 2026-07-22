#pragma once
#include "IEngine.hpp"
#include "render/WindowModule.h"
#include "render/backend/SDLRenderModule.h"
#include "render/ui/UIModule.h"

#include <memory>

#include "script_backend/lua/lua_base.hpp"

class IEngine_impl : public IEngine{
public:
    virtual ~IEngine_impl() = default;

    int  init(int argc, char* argv[]) override;
    void run()                        override;
    void shutdown()                   override;
private:
    SDL_Window*     cached_window;
    bool running  = false;

    WindowModule    window;
    UIModule        ui;

    std::unique_ptr<IRenderModule> render;
};
