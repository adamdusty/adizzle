#include <adizzle/cast.hpp>
#include <adizzle/float.hpp>
#include <adizzle/literals.hpp>
#include <snitch/snitch.hpp>

#include <cmath>
#include <concepts>
#include <cstdint>
#include <limits>

using namespace adizzle;

TEST_CASE("Integral cast from smaller type to larger type same value") {
    std::uint8_t u8   = 10;
    std::uint16_t u16 = 10;
    std::uint32_t u32 = 10;

    std::int8_t i8   = 10;
    std::int16_t i16 = 10;
    std::int32_t i32 = 10;

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
    std::uint16_t u16 = 20;
    std::uint32_t u32 = 20;
    std::uint64_t u64 = 20;

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
    std::uint16_t u16 = ~0_u16;
    std::uint32_t u32 = ~0_u32;
    std::uint64_t u64 = ~0_u64;

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
    CHECK(almost_equal(res, 10.0));
}

TEST_CASE("Float cast double to float succeeds in float range") {
    double x = 10.0;
    auto res = checked_cast<float>(x);
    CHECK(almost_equal(res, 10.0f));
}

TEST_CASE("Float cast double to float fails when larger than float_max") {
    double x = std::numeric_limits<double>::max();
    CHECK_THROWS_AS(checked_cast<float>(x), cast_error);
}

TEST_CASE("Float cast to int succeeds in representable range") {
    float a  = 256.0F;
    double b = 512.0;

    auto res_a = checked_cast<std::int64_t>(a);
    auto res_b = checked_cast<std::int64_t>(b);

    CHECK(res_a == 256_i64);
    CHECK(res_b == 512_i64);
}

TEST_CASE("Float to int cast fails when value is not exactly integer representable.") {
    float x = 33'554'432.0F; // 2^25
    CHECK_THROWS_AS(checked_cast<std::uint64_t>(x), cast_error);
}

TEST_CASE("Float to int cast fails when negative value is not exactly integer representable.") {
    float x = -33'554'432.0F; // 2^25
    CHECK_THROWS_AS(checked_cast<std::int64_t>(x), cast_error);
}

TEST_CASE("Float to int cast fails when value is outside int max.") {
    float a  = 100'000.0f; // Less than 2^(mantissa - 1)
    double b = 100'000.0;  // Less than 2^(mantissa - 1)

    CHECK_THROWS_AS(checked_cast<std::int16_t>(a), cast_error);
    CHECK_THROWS_AS(checked_cast<std::int16_t>(b), cast_error);
}

TEST_CASE("Integral cast to float within exactly representable range succeeds") {
    std::uint64_t x = 8'388'607;
    std::uint64_t y = 4'503'599'627'370'496;
    auto res_f      = checked_cast<float>(x);
    auto res_d      = checked_cast<double>(y);

    // Floating point equality should be okay here since the values should be exactly representable
    // Implicitly converted to doubles anyway, I think
    CHECK(almost_equal(res_f, 8'388'607.000f));
    CHECK(almost_equal(res_d, 4'503'599'627'370'496.000));
}

TEST_CASE("Integral cast fails when outside exact representable range of float") {
    std::uint64_t x = std::numeric_limits<std::uint64_t>::max();

    CHECK_THROWS_AS(checked_cast<float>(x), cast_error);
    CHECK_THROWS_AS(checked_cast<double>(x), cast_error);
}
