#pragma once

#include <bit>
#include <cmath>
#include <concepts>
#include <cstdint>
#include <limits>

namespace adizzle {

template<std::floating_point T>
constexpr auto almost_equal(T a, T b) -> bool {
    using int_type = std::conditional_t<std::is_same_v<T, float>, std::int32_t, std::int64_t>;
    auto a_int     = std::bit_cast<int_type>(a);
    auto b_int     = std::bit_cast<int_type>(b);

    // a & b are exactly the same in memory
    if(a_int == b_int) {
        return true;
    }

    auto a_abs   = std::abs(a);
    auto b_abs   = std::abs(b);
    auto diff    = std::abs(a - b);
    auto max_val = std::max(a_abs, b_abs); // a_abs > b_abs ? a_abs : b_abs;
    auto denorm  = std::numeric_limits<decltype(max_val)>::denorm_min();
    auto epsilon = std::numeric_limits<decltype(max_val)>::epsilon() * max_val;

    if(a == 0 || b == 0 || ((a_abs + b_abs) < denorm)) {
        return diff < (epsilon * denorm);
    }

    return (diff / std::min(a_abs + b_abs, max_val)) < epsilon;
}

template<std::floating_point T>
constexpr auto almost_equal(T a, T b, T diff) -> bool {
    return std::abs(a - b) < diff;
}

} // namespace adizzle