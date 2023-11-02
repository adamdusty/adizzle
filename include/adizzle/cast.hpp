#pragma once

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

namespace details {

template<std::integral To, std::integral From>
constexpr auto integral_cast(const From from) -> To {
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
    if(std::cmp_less(from, to_min)) {
        auto msg = std::format(
            "Narrowing cast less than minimum. Casting {} to type with range [{}, {}]", from, to_min, to_max);
        throw cast_error(msg);
    }

    if(std::cmp_greater(from, to_max)) {
        auto msg = std::format(
            "Narrowing cast greater than maximum. Casting {} to type with range [{}, {}]", from, to_min, to_max);
        throw cast_error(msg);
    }

    return static_cast<To>(from);
}

template<std::floating_point To, std::floating_point From>
constexpr auto floating_point_cast(const From from) -> To {

    auto to_min = std::numeric_limits<To>::min();
    auto to_max = std::numeric_limits<To>::max();
    if(from < to_min) {
        auto msg = std::format(
            "Narrowing cast less than minimum. Casting {} to type with range [{}, {}]", from, to_min, to_max);
        throw cast_error(msg);
    }

    if(from > to_max) {
        auto msg = std::format(
            "Narrowing cast greater than maximum. Casting {} to type with range [{}, {}]", from, to_min, to_max);
        throw cast_error(msg);
    }

    return static_cast<To>(from);
}

} // namespace details

template<typename T>
concept numeric = std::integral<T> || std::floating_point<T>;

template<numeric To, numeric From>
constexpr auto checked_cast(const From from) -> To {
    if constexpr(std::same_as<From, To>) {
        return from;
    }

    // TODO:
    //  - Account for floating point to integral
    //  - Account for floating point to integral not-exact
    //  - Account for floating point to integral when from > To::max()
    //  - Account for integral to floating point
    //  - Account for integral to floating point outside representable range (2^23 float, 2^53 double)

    if constexpr(std::is_integral_v<From> && std::is_integral_v<To>) {
        return details::integral_cast<To>(from);
    } else if constexpr(std::is_floating_point_v<From> && std::is_floating_point_v<To>) {
        return details::floating_point_cast<To>(from);
    } else {
        throw cast_error("Unimplemented");
    }
}

} // namespace adizzle
