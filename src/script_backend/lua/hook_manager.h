#pragma once
#include <string_view>

#include "sol/forward.hpp"

namespace lua{
     void add_hook(std::string_view name, std::string_view id, const sol::function& func);
     void del_hook(std::string_view name, std::string_view id);
     void call_hook(std::string_view name);
}
