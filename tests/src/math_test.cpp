#include <adizzle/float.hpp>
#include <adizzle/math.hpp>
#include <snitch/snitch.hpp>

TEST_CASE("almost equal with diff") {
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