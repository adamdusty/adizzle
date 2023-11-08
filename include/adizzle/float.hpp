#pragma once

#include <cmath>
#include <concepts>
#include <limits>

namespace adizzle {

template<std::floating_point T>
constexpr auto almost_equal(const T a, const T b) -> bool {
    auto a_abs   = std::abs(a);
    auto b_abs   = std::abs(b);
    auto diff    = std::abs(a - b);
    auto max_val = a_abs > b_abs ? a_abs : b_abs;
    auto denorm  = std::numeric_limits<decltype(max_val)>::denorm_min();
    auto epsilon = std::numeric_limits<decltype(max_val)>::epsilon() * max_val;

    if(a == b) {
        return true;
    }

    if(a == 0 || b == 0 || ((a_abs + b_abs) < denorm)) {
        return diff < (epsilon * denorm);
    }

    return (diff / std::min(a_abs + b_abs, max_val)) < epsilon;
}

} // namespace adizzle