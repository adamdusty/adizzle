#include <adizzle/cast.hpp>
#include <adizzle/literals.hpp>
#include <snitch/snitch.hpp>

#include <cmath>
#include <concepts>
#include <cstdint>
#include <limits>

using namespace adizzle;

template<std::floating_point T, std::floating_point U>
constexpr auto almost_equal(const T a, const U b) -> bool {
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

TEST_CASE("Integral cast from smaller type to larger type same value") {
    std::uint8_t u8   = 10;
    std::uint16_t u16 = 10;
    std::uint32_t u32 = 10;
    std::uint64_t u64 = 10;

    std::int8_t i8   = 10;
    std::int16_t i16 = 10;
    std::int32_t i32 = 10;
    std::int64_t i64 = 10;

    CHECK(checked_cast<std::uint16_t>(u8) == u8);
    CHECK(checked_cast<std::uint32_t>(u8) == u8);
    CHECK(checked_cast<std::uint64_t>(u8) == u8);

    CHECK(checked_cast<std::uint32_t>(u16) == u16);
    CHECK(checked_cast<std::uint64_t>(u16) == u16);

    CHECK(checked_cast<std::uint64_t>(u32) == u32);

    CHECK(checked_cast<std::int16_t>(i8) == i8);
    CHECK(checked_cast<std::int32_t>(i8) == i8);
    CHECK(checked_cast<std::int64_t>(i8) == i8);

    CHECK(checked_cast<std::int32_t>(i16) == i16);
    CHECK(checked_cast<std::int64_t>(i16) == i16);

    CHECK(checked_cast<std::int64_t>(i32) == i32);
}

TEST_CASE("Integral cast to smaller type succeeds when value is representable by smaller type") {
    std::uint8_t u8   = 20;
    std::uint16_t u16 = 20;
    std::uint32_t u32 = 20;
    std::uint64_t u64 = 20;

    std::int8_t i8   = 20;
    std::int16_t i16 = 20;
    std::int32_t i32 = 20;
    std::int64_t i64 = 20;

    CHECK(checked_cast<std::uint8_t>(u64) == u64);
    CHECK(checked_cast<std::uint16_t>(u64) == u64);
    CHECK(checked_cast<std::uint32_t>(u64) == u64);

    CHECK(checked_cast<std::uint8_t>(u32) == u32);
    CHECK(checked_cast<std::uint16_t>(u32) == u32);

    CHECK(checked_cast<std::uint8_t>(u16) == u16);

    CHECK(checked_cast<std::int8_t>(i64) == i64);
    CHECK(checked_cast<std::int16_t>(i64) == i64);
    CHECK(checked_cast<std::int32_t>(i64) == i64);

    CHECK(checked_cast<std::int8_t>(i32) == i32);
    CHECK(checked_cast<std::int16_t>(i32) == i32);

    CHECK(checked_cast<std::int8_t>(i16) == i16);
}

TEST_CASE("Integral cast from signed <-> unsigned when value is representable") {
    std::uint8_t u8   = 65;
    std::uint16_t u16 = 65;
    std::uint32_t u32 = 65;
    std::uint64_t u64 = 65;

    std::int8_t i8   = 65;
    std::int16_t i16 = 65;
    std::int32_t i32 = 65;
    std::int64_t i64 = 65;

    CHECK(checked_cast<std::uint8_t>(i8) == 65);
    CHECK(checked_cast<std::uint8_t>(i16) == 65);
    CHECK(checked_cast<std::uint8_t>(i32) == 65);
    CHECK(checked_cast<std::uint8_t>(i64) == 65);

    CHECK(checked_cast<std::int8_t>(u8) == 65);
    CHECK(checked_cast<std::int8_t>(u16) == 65);
    CHECK(checked_cast<std::int8_t>(u32) == 65);
    CHECK(checked_cast<std::int8_t>(u64) == 65);

    CHECK(checked_cast<std::uint16_t>(i8) == 65);
    CHECK(checked_cast<std::uint16_t>(i16) == 65);
    CHECK(checked_cast<std::uint16_t>(i32) == 65);
    CHECK(checked_cast<std::uint16_t>(i64) == 65);

    CHECK(checked_cast<std::int16_t>(u8) == 65);
    CHECK(checked_cast<std::int16_t>(u16) == 65);
    CHECK(checked_cast<std::int16_t>(u32) == 65);
    CHECK(checked_cast<std::int16_t>(u64) == 65);

    CHECK(checked_cast<std::uint32_t>(i8) == 65);
    CHECK(checked_cast<std::uint32_t>(i16) == 65);
    CHECK(checked_cast<std::uint32_t>(i32) == 65);
    CHECK(checked_cast<std::uint32_t>(i64) == 65);

    CHECK(checked_cast<std::int32_t>(u8) == 65);
    CHECK(checked_cast<std::int32_t>(u16) == 65);
    CHECK(checked_cast<std::int32_t>(u32) == 65);
    CHECK(checked_cast<std::int32_t>(u64) == 65);

    CHECK(checked_cast<std::uint64_t>(i8) == 65);
    CHECK(checked_cast<std::uint64_t>(i16) == 65);
    CHECK(checked_cast<std::uint64_t>(i32) == 65);
    CHECK(checked_cast<std::uint64_t>(i64) == 65);

    CHECK(checked_cast<std::int64_t>(u8) == 65);
    CHECK(checked_cast<std::int64_t>(u16) == 65);
    CHECK(checked_cast<std::int64_t>(u32) == 65);
    CHECK(checked_cast<std::int64_t>(u64) == 65);
}

TEST_CASE("Integral cast throws when casting negative value to unsigned") {
    std::uint8_t u8   = 30;
    std::uint16_t u16 = 30;
    std::uint32_t u32 = 30;
    std::uint64_t u64 = 30;

    std::int8_t i8   = -30;
    std::int16_t i16 = -30;
    std::int32_t i32 = -30;
    std::int64_t i64 = -30;

    CHECK_THROWS_AS(checked_cast<std::uint8_t>(i8), cast_error);
    CHECK_THROWS_AS(checked_cast<std::uint16_t>(i16), cast_error);
    CHECK_THROWS_AS(checked_cast<std::uint32_t>(i32), cast_error);
    CHECK_THROWS_AS(checked_cast<std::uint64_t>(i64), cast_error);
}

TEST_CASE("Integral cast throws when casting unsigned to same size int outside of its representable range") {
    std::uint8_t u8   = ~0_u8;
    std::uint16_t u16 = ~0_u16;
    std::uint32_t u32 = ~0_u32;
    std::uint64_t u64 = ~0_u64;

    CHECK_THROWS_AS(checked_cast<std::int8_t>(u8), cast_error);
    CHECK_THROWS_AS(checked_cast<std::int16_t>(u16), cast_error);
    CHECK_THROWS_AS(checked_cast<std::int32_t>(u32), cast_error);
    CHECK_THROWS_AS(checked_cast<std::int64_t>(u64), cast_error);
}

TEST_CASE("Integral cast throws when casting to smaller type that cannot represent the value") {
    std::uint8_t u8   = ~0_u8;
    std::uint16_t u16 = ~0_u16;
    std::uint32_t u32 = ~0_u32;
    std::uint64_t u64 = ~0_u64;

    std::int8_t i8   = 127_i8;
    std::int16_t i16 = 32'767;
    std::int32_t i32 = 2'147'483'647;
    std::int64_t i64 = 9'223'372'036'854'775'807;

    CHECK_THROWS_AS(checked_cast<std::uint8_t>(u64), cast_error);
    CHECK_THROWS_AS(checked_cast<std::uint16_t>(u64), cast_error);
    CHECK_THROWS_AS(checked_cast<std::uint32_t>(u64), cast_error);

    CHECK_THROWS_AS(checked_cast<std::uint8_t>(u32), cast_error);
    CHECK_THROWS_AS(checked_cast<std::uint16_t>(u32), cast_error);

    CHECK_THROWS_AS(checked_cast<std::uint8_t>(u16), cast_error);

    CHECK_THROWS_AS(checked_cast<std::int8_t>(i64), cast_error);
    CHECK_THROWS_AS(checked_cast<std::int16_t>(i64), cast_error);
    CHECK_THROWS_AS(checked_cast<std::int32_t>(i64), cast_error);

    CHECK_THROWS_AS(checked_cast<std::int8_t>(i32), cast_error);
    CHECK_THROWS_AS(checked_cast<std::int16_t>(i32), cast_error);

    CHECK_THROWS_AS(checked_cast<std::int8_t>(i16), cast_error);
}

TEST_CASE("Float cast float to double succeeds") {
    float x  = 10.0F;
    auto res = checked_cast<double>(x);
    CHECK(almost_equal(res, x));
}