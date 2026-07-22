#pragma once

#include <concepts>

namespace math{
    template<std::floating_point T>
    [[nodiscard]] constexpr T lerp(T from, T to, T t) noexcept {
        return from + (to - from) * t;
    }
    template<std::floating_point T>
    [[nodiscard]] constexpr T true_lerp(T from, T to, T t) noexcept {
        return (T{1}-t)*from + t*to;
    }
}