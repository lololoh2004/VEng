#pragma once

enum class Presets{
    Full,
    NoFFI
};
void init_api(Presets preset);