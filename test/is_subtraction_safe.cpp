#include <iostream>

#include "../deps/catch.h"
#include "../numeric_utility.h"


TEST_CASE("is_subtraction_safe() for signed values returns true if subtraction op is safe") {
  using namespace iron::numeric;
  
  REQUIRE(true == is_subtraction_safe(0, 0));
  REQUIRE(true == is_subtraction_safe(3, 6));
  REQUIRE(true == is_subtraction_safe(-3, 6));
  REQUIRE(true == is_subtraction_safe(3, -6));
  REQUIRE(true == is_subtraction_safe(static_cast<char>(-64), static_cast<char>(-70)));
  REQUIRE(false == is_subtraction_safe(0, std::numeric_limits<int>::min()));
  REQUIRE(false == is_subtraction_safe(-1, std::numeric_limits<int>::min()));
}

TEST_CASE("is_subtraction_safe() for mixed-sign values returns true if subtraction op is safe") {
  using namespace iron::numeric;
  
  REQUIRE(true == is_subtraction_safe(0ll, 0u));
  REQUIRE(true == is_subtraction_safe(3ll, 6u));
  REQUIRE(true == is_subtraction_safe(-3ll, 6u));
  REQUIRE(true == is_subtraction_safe(0ll, std::numeric_limits<unsigned int>::min()));
  REQUIRE(false == is_subtraction_safe(-1ll, std::numeric_limits<unsigned int>::min()));

  REQUIRE(true == is_subtraction_safe(0u, 0ll));
  REQUIRE(true == is_subtraction_safe(3u, 6ll));
  REQUIRE(true == is_subtraction_safe(-3u, 6ll));
  REQUIRE(true == is_subtraction_safe(0u, std::numeric_limits<long long>::min()));
  REQUIRE(false == is_subtraction_safe(-1u, std::numeric_limits<long long>::min()));
}