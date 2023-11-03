#pragma once

#include <cmath>
#include <concepts>
#include <cstdint>
#include <format>
#include <limits>
#include <stdexcept>
#include <type_traits>
#include <utility>

namespace adizzle {

struct cast_error : std::logic_error {
    using std::logic_error::logic_error;
};

template<typename T>
concept numeric = std::integral<T> || std::floating_point<T>;

namespace details {

template<std::integral To, std::integral From>
constexpr auto int_cast(const From from) -> To {
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
constexpr auto fp_cast(const From from) -> To {

    auto to_min = std::numeric_limits<To>::min();
    auto to_max = std::numeric_limits<To>::max();
    if(from < to_min || from > to_max) {
        auto msg = std::format("Undesirable cast result. Casting {} to type with range [{}, {}]", from, to_min, to_max);
        throw cast_error(msg);
    }

    return static_cast<To>(from);
}

template<std::integral To, std::floating_point From>
constexpr auto fp_to_int_cast(const From from) -> To {
    auto to_min = std::numeric_limits<To>::min();
    auto to_max = std::numeric_limits<To>::max();
    if(from < to_min || from > to_max) {
        auto msg =
            std::format("Undesirable cast result. Casting `{}` to type with range [{}, {}]", from, to_min, to_max);
        throw cast_error(msg);
    }

    auto max_exact_int = std::pow(2, std::numeric_limits<From>::digits - 1);
    if(std::abs(from) > max_exact_int) {
        auto msg = std::format(
            "Undesirable cast result. Casting floating point number `{}` beyond maximum exact representable integer {}",
            from,
            max_exact_int);
        throw cast_error(msg);
    }

    return static_cast<To>(from);
}

template<std::floating_point To, std::integral From>
auto int_to_fp_cast(const From from) -> To {

    auto max_exact = std::pow(2, std::numeric_limits<To>::digits - 1);
    From abs       = from;

    // std::abs only defined for signed integers
    if constexpr(std::is_signed_v<From>) {
        abs = std::abs(from);
    }

    if(abs > max_exact) {
        auto msg = std::format(
            "Undesirable cast result. Casting integer `{}` beyond maximum exact representable floating point number {}",
            from,
            max_exact);
        throw cast_error(msg);
    }

    return static_cast<To>(from);
}

} // namespace details

template<numeric To, numeric From>
constexpr auto checked_cast(const From from) -> To {
    if constexpr(std::same_as<From, To>) {
        return from;
    }

    if constexpr(std::is_integral_v<From> && std::is_integral_v<To>) {
        return details::int_cast<To>(from);
    } else if constexpr(std::is_floating_point_v<From> && std::is_floating_point_v<To>) {
        return details::fp_cast<To>(from);
    } else if constexpr(std::is_floating_point_v<From> && std::is_integral_v<To>) {
        return details::fp_to_int_cast<To>(from);
    } else if(std::is_integral_v<From> && std::is_floating_point_v<To>) {
        return details::int_to_fp_cast<To>(from);
    } else {
        throw cast_error("Unimplemented");
    }
}

// Converts to static_cast<To>(from) in NDEBUG
// Otherwise, checks if cast causes undesirable behavior
template<numeric To, numeric From>
constexpr auto debug_cast(const From from) -> To {
#if defined(NDEBUG) && NDEBUG
    return static_cast<To>(from);
#else
    checked_cast<To>(from);
#endif
}

} // namespace adizzle
