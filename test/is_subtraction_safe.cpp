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
}

TEST_CASE("is_subtraction_safe() for signed values returns false if subtraction op is unsafe") {
  using namespace iron::numeric;

  REQUIRE(false == is_subtraction_safe(0, std::numeric_limits<int>::min()));
  REQUIRE(false == is_subtraction_safe(static_cast<int>(-1), std::numeric_limits<int>::min()));
}

TEST_CASE("is_subtraction_safe() for unsigned values returns true if subtraction op is safe") {
  using namespace iron::numeric;

  REQUIRE(true == is_subtraction_safe(0u, 0u));
  REQUIRE(true == is_subtraction_safe(6u, 0u));
  REQUIRE(true == is_subtraction_safe(6u, 3u));

  REQUIRE(
    true == is_subtraction_safe(
      std::numeric_limits<uint8_t>::max(), std::numeric_limits<uint8_t>::max()
    )
  );
}

TEST_CASE("is_subtraction_safe() for unsigned values returns false if subtraction op is unsafe") {
  using namespace iron::numeric;

  REQUIRE(false == is_subtraction_safe(0u, 1u));
  REQUIRE(false == is_subtraction_safe(0u, std::numeric_limits<unsigned int>::max()));
}
