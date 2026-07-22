#pragma once

class IEngine{
public:
    virtual ~IEngine() = default;

    virtual int init(int argc, char* argv[]) = 0;
    virtual void run() = 0;
    virtual void shutdown() = 0;
};
