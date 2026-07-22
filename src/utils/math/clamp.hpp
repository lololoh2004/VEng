#pragma once

#include <concepts>

namespace math{
    template<std::totally_ordered  T>
    [[nodiscard]] constexpr T clamp(T input, T min, T max) noexcept {
        if (input < min) return min;
        if (input > max) return max;
        return input;
    }
}