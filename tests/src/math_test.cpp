#include <adizzle/float.hpp>
#include <adizzle/math.hpp>
#include <snitch/snitch.hpp>

TEST_CASE("constexpr abs") {
    auto a = 10;
    auto b = -10;
    auto c = 3.14159f;
    auto d = -3.14159f;
    auto e = 3.14159;
    auto f = -3.14159;

    CHECK(adizzle::abs(a) == 10);
    CHECK(adizzle::abs(b) == 10);
    CHECK(adizzle::almost_equal(adizzle::abs(c), 3.14159f, 0.00001f));
    CHECK(adizzle::almost_equal(adizzle::abs(d), 3.14159f, 0.00001f));
    CHECK(adizzle::almost_equal(adizzle::abs(e), 3.14159, 0.00001));
    CHECK(adizzle::almost_equal(adizzle::abs(f), 3.14159, 0.00001));
}

TEST_CASE("constexpr sqrt") {
    auto a = 100;
    auto b = 100.0f;
    auto c = 100.0;

    CHECK(adizzle::almost_equal(adizzle::sqrt(a), 10.0, 0.00001));
    CHECK(adizzle::almost_equal(adizzle::sqrt(b), 10.0f, 0.00001f));
    CHECK(adizzle::almost_equal(adizzle::sqrt(c), 10.0, 0.00001));
}