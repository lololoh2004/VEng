#pragma once
#include "sol/state.hpp"

#include "term/term_wrapper.hpp"

namespace lua{
    inline sol::state& get_state(){
        static sol::state state;
        return state;
    }
    inline bool test_run(){
        auto& state = get_state();
        if (state.script("return true --test")) {
            term::msg("[LUA] INFO : Test script execution successful\n");
            return true;
        }
        term::msg("[LUA] INFO : Test script execution FAILED\n");
        return false;
    }
    // template <typename T>
    // T run(const char* path){
    //     auto& state = get_state();
    //     return T{-9};
    // }
    inline bool init(){
        auto& state = get_state();

        state.open_libraries(
            sol::lib::base,sol::lib::string,
            sol::lib::table, sol::lib::ffi);
        term::msg("[LUA] INFO : Lua library initialization successful\n");
        return test_run();
    }
}