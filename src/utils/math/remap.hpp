#pragma once

#include <concepts>

#include "clamp.hpp"
#include "lerp.hpp"

namespace math{
    enum class RemapMode{
        Optimized,
        Clamped,
        MaxPrecision
    };

    template<std::floating_point T, RemapMode Mode=RemapMode::Optimized>
    [[nodiscard]] constexpr T remap(T val, T inMin, T inMax, T outMin, T outMax) noexcept {
        if (inMin == inMax) return outMin;

        if constexpr (Mode == RemapMode::Clamped){
            T clamped_val = math::clamp(val, inMin, inMax);
            T t = (clamped_val - inMin) / (inMax - inMin);
            return math::lerp(t, outMin, outMax);
        } else if constexpr (Mode == RemapMode::MaxPrecision){
            T t = (val - inMin) / (inMax - inMin);
            return math::true_lerp(t, outMin, outMax);
        } else{
            T t = (val - inMin) / (inMax - inMin);
            return math::lerp(t, outMin, outMax);
        }
    }
}