#include "interfaces/IEngine.hpp"
#include "interfaces/IEngine_impl.h"
#include "term/term_wrapper.hpp"

//#include "utils/math/all_math.h"
// all_math is just only include .h file

int main(int argc, char* argv[]) {
    term::msg("All arg : ", argc, "\nArg content : ",argv, "\n");
    //auto core = std::make_unique<IEngine_impl>();

    IEngine* core = new IEngine_impl();

    if (core->init(argc, argv) != 0){
        term::msg("[SYS] FATAL_ERROR : Init module failure\n");
        return -1;
    }
    core->run();
    core->shutdown();

    delete core;

    // double temp = math::neg(-12.000000);
    // term::msg(math::abs(temp));

    return 0;
}
