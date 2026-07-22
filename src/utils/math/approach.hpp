#pragma once

#include <concepts>
#include "abs.h"

namespace math{
    template<std::floating_point T>
    [[nodiscard]] constexpr T approach(T current, T target, T change) noexcept {
        if (math::abs(target - current) <= math::abs(change))
            return target;
        T abs_change = math::abs(change);
        return current + ( current < target ? abs_change : -abs_change );
    }
}
