#include <adizzle/float.hpp>
#include <snitch/snitch.hpp>

TEST_CASE("almost equal with diff") {
    CHECK(adizzle::almost_equal(24.00005f, 24.0f, 0.0001f));
}