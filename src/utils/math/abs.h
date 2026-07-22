#pragma once

#include <bit>
#include <cstdint>

namespace math{
    [[nodiscard]] constexpr int abs(int x) noexcept {
        return x >= 0 ? x : -x;
    }
    [[nodiscard]] constexpr float abs(float val) noexcept {
        auto bits = std::bit_cast<uint32_t>(val);
        bits &= 0x7FFFFFFF;
        return std::bit_cast<float>(bits);
    }
    [[nodiscard]] constexpr double abs(double val) noexcept{
        auto bits = std::bit_cast<uint64_t>(val);
        bits &= 0x7FFFFFFFFFFFFFFF;
        return std::bit_cast<double>(bits);
    }
}