#pragma once

class IRenderModule{
public:
    virtual ~IRenderModule() = default;

    virtual bool init()         = 0;
    virtual void update()       = 0;
    virtual void shutdown()     = 0;
};