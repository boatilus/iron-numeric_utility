#include "../numeric_utility.h"

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "../deps/catch.h"


TEST_CASE("is_positive returns all correct results") {
  using namespace iron::numeric;

  static_assert(is_positive(3), "is_positive should be constexpr-callable");
  
  REQUIRE(is_positive(1));
  REQUIRE(is_positive(3));
  REQUIRE(is_positive(474));
  REQUIRE(is_positive(std::numeric_limits<int>::max()));
  REQUIRE(is_positive(std::numeric_limits<uint64_t>::max()));
  
  REQUIRE(!is_positive(0));
  REQUIRE(!is_positive(-1));
  REQUIRE(!is_positive(-3));
  REQUIRE(!is_positive(-474));
  REQUIRE(!is_positive(std::numeric_limits<int>::min()));
  REQUIRE(!is_positive(std::numeric_limits<int64_t>::min()));
}