#include "../numeric_utility.h"
#include "../deps/catch.h"


TEST_CASE("is_negative() returns all correct results") {
  using namespace iron::numeric;

  static_assert(is_negative(-3), "is_negative() should be constexpr-callable");
  
  REQUIRE(!is_negative(1));
  REQUIRE(!is_negative(3));
  REQUIRE(!is_negative(474));
  REQUIRE(!is_negative(std::numeric_limits<int>::max()));
  REQUIRE(!is_negative(std::numeric_limits<uint64_t>::max()));
  
  REQUIRE(is_negative(-1));
  REQUIRE(is_negative(-3));
  REQUIRE(is_negative(-474));
  REQUIRE(is_negative(std::numeric_limits<int>::min()));
  REQUIRE(is_negative(std::numeric_limits<int64_t>::min()));
}