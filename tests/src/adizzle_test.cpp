#include <snitch/snitch.hpp>
#include <adizzle/adizzle.hpp>

TEST_CASE("Test case", "[greeting]") {
    REQUIRE(adizzle::get_version() == 1);
}