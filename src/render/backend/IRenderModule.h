#pragma once

class IRenderModule{
public:
    virtual ~IRenderModule() = default;

    virtual bool init()         = 0;
    virtual void begin_render() = 0;
    virtual void end_render()   = 0;
    virtual void shutdown()     = 0;
};