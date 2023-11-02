#pragma once

#include <cstdint>

namespace adizzle {

inline auto operator"" _u8(unsigned long long val) -> std::uint8_t {
    return static_cast<std::uint8_t>(val);
}

inline auto operator"" _u16(unsigned long long val) -> std::uint16_t {
    return static_cast<std::uint16_t>(val);
}

inline auto operator"" _u32(unsigned long long val) -> std::uint32_t {
    return static_cast<std::uint32_t>(val);
}

inline auto operator"" _u64(unsigned long long val) -> std::uint64_t {
    return static_cast<std::uint64_t>(val);
}

inline auto operator"" _i8(unsigned long long val) -> std::int8_t {
    return static_cast<std::int8_t>(val);
}

inline auto operator"" _i16(unsigned long long val) -> std::int16_t {
    return static_cast<std::int16_t>(val);
}

inline auto operator"" _i32(unsigned long long val) -> std::int32_t {
    return static_cast<std::int32_t>(val);
}

inline auto operator"" _i64(unsigned long long val) -> std::int64_t {
    return static_cast<std::int64_t>(val);
}

} // namespace adizzle