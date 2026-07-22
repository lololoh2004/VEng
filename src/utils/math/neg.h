#pragma once

#include <bit>
#include <cstdint>

namespace math{
    [[nodiscard]] constexpr int neg(int val) noexcept {
        return -val;
    }
    [[nodiscard]] constexpr float neg(float val) noexcept {
        auto bits = std::bit_cast<uint32_t>(val);
        bits ^= 0x80000000;
        return std::bit_cast<float>(bits);
    }
    [[nodiscard]] constexpr double neg(double val) noexcept {
        auto bits = std::bit_cast<uint64_t>(val);
        bits ^= 0x8000000000000000ULL;
        return std::bit_cast<double>(bits);
    }
}