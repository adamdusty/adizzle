#pragma once

#include <cmath>
#include <cstdint>
#include <format>
#include <limits>
#include <stdexcept>
#include <type_traits>
#include <utility>

#include "adizzle/concepts.hpp"

namespace adizzle {

using std::numeric_limits;

struct cast_error : std::logic_error {
    using std::logic_error::logic_error;
};

namespace detail {

template<std::integral To, std::integral From>
auto int_cast(const From from) -> To {
    // Throw a cast_error if casting from a signed int with a negative value to an unsigned int
    if constexpr(std::is_signed_v<From> && std::is_unsigned_v<To>) {
        if(from < 0) {
            auto msg = std::format(
                "Casting signed type with negative value `{}` to unsigned type. Unlikely to be desired behavior.",
                from);
            throw cast_error(msg);
        }
    }

    auto to_min = std::numeric_limits<To>::min();
    auto to_max = std::numeric_limits<To>::max();
    if(std::cmp_less(from, to_min) || std::cmp_greater(from, to_max)) {
        auto msg = std::format("Undesirable cast result. Casting {} to type with range [{}, {}]", from, to_min, to_max);
        throw cast_error(msg);
    }

    return static_cast<To>(from);
}

template<std::floating_point To, std::floating_point From>
auto fp_cast(const From from) -> To {

    auto to_min = std::numeric_limits<To>::min();
    auto to_max = std::numeric_limits<To>::max();
    if(static_cast<double>(from) < static_cast<double>(to_min) ||
       static_cast<double>(from) > static_cast<double>(to_max)) {
        auto msg = std::format("Undesirable cast result. Casting {} to type with range [{}, {}]", from, to_min, to_max);
        throw cast_error(msg);
    }

    return static_cast<To>(from);
}

template<std::integral To, std::floating_point From>
auto fp_to_int_cast(const From from) -> To {

    auto max_exact_int = static_cast<From>(std::pow(2, std::numeric_limits<From>::digits - 1));
    if(std::abs(from) > max_exact_int) {
        auto msg = std::format(
            "Undesirable cast result. Casting floating point number `{}` beyond maximum exact representable integer {}",
            from,
            max_exact_int);
        throw cast_error(msg);
    }

    auto to_min = static_cast<From>(numeric_limits<To>::min());
    auto to_max = static_cast<From>(numeric_limits<To>::max());
    if(from < to_min || from > to_max) {
        auto msg =
            std::format("Undesirable cast result. Casting `{}` to type with range [{}, {}]", from, to_min, to_max);
        throw cast_error(msg);
    }

    return static_cast<To>(from);
}

template<std::floating_point To, std::integral From>
auto int_to_fp_cast(const From from) -> To {

    auto max_exact = static_cast<std::int64_t>(std::pow(2, std::numeric_limits<To>::digits - 1));
    From abs       = from;

    // std::abs only defined for signed integers
    if constexpr(std::is_signed_v<From>) {
        abs = std::abs(from);
    }

    if(std::cmp_greater(abs, max_exact)) {
        auto msg = std::format(
            "Undesirable cast result. Casting integer `{}` beyond maximum exact representable floating point number {}",
            from,
            max_exact);
        throw cast_error(msg);
    }

    return static_cast<To>(from);
}

} // namespace detail

template<numeric To, numeric From>
auto checked_cast(const From from) -> To {
    if constexpr(std::same_as<From, To>) {
        return from;
    }

    if constexpr(std::is_integral_v<From> && std::is_integral_v<To>) {
        return detail::int_cast<To>(from);
    } else if constexpr(std::is_floating_point_v<From> && std::is_floating_point_v<To>) {
        return detail::fp_cast<To>(from);
    } else if constexpr(std::is_floating_point_v<From> && std::is_integral_v<To>) {
        return detail::fp_to_int_cast<To>(from);
    } else if(std::is_integral_v<From> && std::is_floating_point_v<To>) {
        return detail::int_to_fp_cast<To>(from);
    } else {
        throw cast_error("Unimplemented");
    }
}

// Converts to static_cast<To>(from) in NDEBUG
// Otherwise, checks if cast causes undesirable behavior
template<numeric To, numeric From>
auto debug_cast(const From from) -> To {
#if defined(NDEBUG) && NDEBUG
    return static_cast<To>(from);
#else
    return checked_cast<To>(from);
#endif
}

} // namespace adizzle
