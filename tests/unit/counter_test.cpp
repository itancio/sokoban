#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../../src/counter.hpp"

TEST_CASE("initial value should be 0") {
    Counter c{};
    CHECK(c.count == 0);
}

TEST_CASE("value after increment should be 1") {
    Counter c{};
    c.increment();
    CHECK(c.count == 1);
}
