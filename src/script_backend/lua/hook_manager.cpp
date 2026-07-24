#include "hook_manager.h"

#include "lua_base.hpp"

// THIS IS A MODULE FROM lua_base.hpp

namespace lua{
    // THESE 3 FUNCTIONS IS ON SKETCH STATE
    void add_hook(std::string_view name, std::string_view id, const sol::function& func){
        hooks[std::string(name)].push_back({std::string(id), func});
    }
    // THESE 3 FUNCTIONS IS ON SKETCH STATE
    void del_hook(std::string_view name, std::string_view id){
        std::erase_if(hooks[std::string(name)], [&](const CallbackEl& el) {
            return el.id == id;
        });
    }
    // THESE 3 FUNCTIONS IS ON SKETCH STATE
    void call_hook(std::string_view name){
        auto& hook_vec = hooks[std::string(name)];
        for (auto& hook : hook_vec) {
            if (!hook.func.valid()) continue;

            auto result = hook.func();

            if (result.valid()) continue;

            sol::error err = result;
            term::msg("\n[LUA ERROR] : ");
            term::msg(err.what());
            term::msg("\n");
        }
    }
}
