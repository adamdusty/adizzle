#pragma once

#include "adizzle/concepts.hpp"
#include "adizzle/float.hpp"
#include <bit>
#include <concepts>
#include <cstdint>
#include <limits>
#include <type_traits>

namespace adizzle {

namespace detail {

template<std::floating_point T>
constexpr auto sqrt_newton_raphson(T num, T curr, T prev) -> T {
    return adizzle::almost_equal(curr, prev)
               ? curr
               : sqrt_newton_raphson(num, static_cast<T>(0.5) * (curr + num / curr), curr);
}

} // namespace detail

template<std::floating_point T>
constexpr auto fabs(T num) -> T {
    if constexpr(sizeof(T) == sizeof(std::uint32_t)) {
        auto ret  = std::bit_cast<std::uint32_t>(num);
        auto mask = std::bit_cast<std::uint32_t>(std::numeric_limits<std::int32_t>::max());
        return std::bit_cast<T>(ret & mask);
    } else if constexpr(sizeof(T) == sizeof(std::uint64_t)) {
        auto ret  = std::bit_cast<std::uint64_t>(num);
        auto mask = std::bit_cast<std::uint64_t>(std::numeric_limits<std::int64_t>::max());
        return std::bit_cast<T>(ret & mask);
    }
}

template<std::integral T>
constexpr auto iabs(T num) -> T {
    auto mask = num >> (sizeof(num) - 1);
    return ((num + mask) ^ mask);
}

template<numeric T>
constexpr auto abs(T num) -> T {
    if constexpr(std::is_floating_point_v<T>) {
        return fabs(num);
    } else {
        return iabs(num);
    }
}

template<std::floating_point T>
constexpr auto sqrt(T num) -> std::floating_point auto {
    return num >= 0 && num < std::numeric_limits<T>::infinity()
               ? detail::sqrt_newton_raphson(num, num, static_cast<T>(0))
               : std::numeric_limits<T>::quiet_NaN();
}

template<std::integral T>
constexpr auto sqrt(T num) -> std::floating_point auto {
    return sqrt(static_cast<double>(num));
}

} // namespace adizzle