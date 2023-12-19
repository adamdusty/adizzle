#include <adizzle/string.hpp>
#include <snitch/snitch.hpp>

#include <string>

TEST_CASE("ltrim") {
    auto input    = std::string("  data");
    auto actual   = adizzle::ltrim(input);
    auto expected = std::string("data");
    CHECK(actual == expected);

    input    = std::string("      princess");
    actual   = adizzle::ltrim(input);
    expected = std::string("princess");
    CHECK(actual == expected);

    input    = std::string("                        apple");
    actual   = adizzle::ltrim(input);
    expected = std::string("apple");
    CHECK(actual == expected);

    input    = std::string(" king kong");
    actual   = adizzle::ltrim(input);
    expected = std::string("king kong");
    CHECK(actual == expected);
}

TEST_CASE("rtrim") {
    auto input = std::string("data  ");

    auto actual   = adizzle::rtrim(input);
    auto expected = std::string("data");
    CHECK(actual == expected);

    input    = std::string("kingdom        ");
    actual   = adizzle::rtrim(input);
    expected = std::string("kingdom");
    CHECK(actual == expected);

    input    = std::string("asdfghjkl               ");
    actual   = adizzle::rtrim(input);
    expected = std::string("asdfghjkl");
    CHECK(actual == expected);
}

TEST_CASE("trim") {
    auto input    = std::string("  data  ");
    auto actual   = adizzle::trim(input);
    auto expected = std::string("data");
    CHECK(actual == expected);

    input    = std::string("  cauliflower  ");
    actual   = adizzle::trim(input);
    expected = std::string("cauliflower");
    CHECK(actual == expected);

    input    = std::string("  expect  ");
    actual   = adizzle::trim(input);
    expected = std::string("expect");
    CHECK(actual == expected);

    input    = std::string("  pregnancy  ");
    actual   = adizzle::trim(input);
    expected = std::string("pregnancy");
    CHECK(actual == expected);
}

TEST_CASE("split") {
    auto input = std::string("11,22,33,44,55,66");

    auto actual   = adizzle::split(input, ',');
    auto expected = std::vector<std::string>{"11", "22", "33", "44", "55", "66"};

    CHECK(actual == expected);
}

TEST_CASE("split") {
    auto input = std::string("11,22,33,44,55,66,");

    auto actual   = adizzle::split(input, ',');
    auto expected = std::vector<std::string>{"11", "22", "33", "44", "55", "66"};

    CHECK(actual == expected);
}

TEST_CASE("contains") {
    auto input = std::string("Hello, world");

    CHECK(adizzle::contains(input, ", wo"));
    CHECK_FALSE(adizzle::contains(input, "abc"));
}