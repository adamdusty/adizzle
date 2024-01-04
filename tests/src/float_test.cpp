#include <adizzle/float.hpp>
#include <snitch/snitch.hpp>

TEST_CASE("amost_equal") {
    float x = 3.14159f;
    float y = 3.14159f;

    auto result = adizzle::almost_equal(x, y);

    CHECK(result);
}

TEST_CASE("amost_equal pos/neg zero") {
    float x = +0.0f;
    float y = -0.0f;

    auto result = adizzle::almost_equal(x, y);

    CHECK(result);
}

TEST_CASE("almost equal with diff") {
    CHECK(adizzle::almost_equal(24.00005f, 24.0f, 0.0001f));
}