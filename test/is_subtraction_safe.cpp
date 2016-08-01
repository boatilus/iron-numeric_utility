#include <future>
#include <iostream>

#include "../deps/catch.h"
#include "../numeric_utility.h"


TEST_CASE("is_subtraction_safe() for signed values returns true if subtraction op is safe") {
  using namespace iron::numeric;

  static_assert(
    true == is_subtraction_safe(3, 6),
    "is_subtraction_safe() for signed values should be constexpr-callable"
  );
  
  REQUIRE(true == is_subtraction_safe(0, 0));
}