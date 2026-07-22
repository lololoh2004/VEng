#pragma once
#include "IEngine.hpp"
#include "render/WindowModule.h"
#include "render/backend/SDLRenderModule.h"
#include "render/ui/UIModule.h"

class IEngine_impl : public IEngine{
public:
    virtual ~IEngine_impl() = default;

    int  init(int argc, char* argv[]) override;
    void run()                        override;
    void shutdown()                   override;
private:
    bool running = false;
    //ScriptModule    script;
    WindowModule    window;
    UIModule        ui;
    SDLRenderModule render;
    //VKRenderModule render;
};
