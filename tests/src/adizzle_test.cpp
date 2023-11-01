#include <adizzle/adizzle.hpp>
#include <adizzle/assert.hpp>
#include <snitch/snitch.hpp>

TEST_CASE("Assert") {
    adizzle::assert(false, "testing");
}