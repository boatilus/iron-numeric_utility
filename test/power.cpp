#include <iostream>

#include "../deps/catch.h"
#include "../numeric_utility.h"


TEST_CASE("power() returns correct result") {
  using namespace iron::numeric;

  static_assert(4 == power(2, 2), "power(2, 2) should be constexpr-callable");

  REQUIRE(1 == power(1, 0));
  REQUIRE(1 == power(1, 1));
  REQUIRE(1 == power(1, 256));
  REQUIRE(1 == power(2, 0));
  REQUIRE(2 == power(2, 1));
  REQUIRE(4 == power(2, 2));
  REQUIRE(8 == power(2, 3));
  REQUIRE(16 == power(2, 4));
  REQUIRE(32 == power(2, 5));
  REQUIRE(64 == power(2, 6));
  REQUIRE(128 == power(2, 7));
}
