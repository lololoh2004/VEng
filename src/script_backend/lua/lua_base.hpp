#pragma once
#include "sol/state.hpp"

#include "term/term_wrapper.hpp"

namespace lua{
    enum class RunMode{
        Fast,
        Secure
    };

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
    inline bool init(){
        auto& state = get_state();

        state.open_libraries(
            sol::lib::base,sol::lib::string,
            sol::lib::table, sol::lib::ffi);
        term::msg("[LUA] INFO : Lua library initialization successful\n");
        return test_run();
    }

    template <typename T=void, RunMode Mode=RunMode::Secure, size_t return_index=0>
    T run(const char* path){
        auto& state = get_state();
        sol::protected_function_result result;

        if constexpr (Mode == RunMode::Secure){
            result = state.script_file(path, sol::script_pass_on_error);

            if (!result.valid()){
                sol::error err = result;
                term::msg("[LUA] ERROR : Failed to load script file. Details:\n",
                          "   File path : ", path, "\n",
                          "   Reason    : ", err.what(), "\n");
                if constexpr (std::is_void_v<T>) return;
                return T{};
            }
        } else{
            result = state.do_file(path);
        }
        if constexpr (std::is_void_v<T>){
            return;
        } else {
            if (result.return_count() == 0){
                if constexpr (Mode == RunMode::Secure){
                    term::msg("[LUA] ERROR : Return value is nothing, but engine expected T{}\n");
                }
                return T{};
            } else
            if constexpr (Mode == RunMode::Secure){
                if (result[return_index].get_type() != sol::type_of<T>()){
                    term::msg("[LUA] ERROR : The return value does not match the required\n   "
                              "(Or the required value falls out of bounds)\n");
                    return T{};
                }
            }
            if (return_index < result.return_count()) {
                return result[return_index].get<T>();
            }
            return result[0].get<T>();
        }
    }
}