#include <iostream>

#include "../deps/catch.h"
#include "../numeric_utility.h"


char operator "" _i8(unsigned long long v) { return static_cast<char>(v); }


TEST_CASE("is_multiplcation_safe() for signed values returns true if multiplication op is safe") {
  using namespace iron::numeric;
  
  static_assert(
    true == is_multiplication_safe(1, 1),
    "is_multiplication_safe(1, 1) should be constexpr-callable"
  );
  
  REQUIRE(true == is_multiplication_safe(1, 2));
  REQUIRE(true == is_multiplication_safe(2, 2));
  REQUIRE(true == is_multiplication_safe(3, 2));
  REQUIRE(true == is_multiplication_safe(6, 2));
  REQUIRE(true == is_multiplication_safe(6, 8));
  REQUIRE(true == is_multiplication_safe(11_i8, 11_i8));  // 121
  
  REQUIRE(true == is_multiplication_safe(-1, 2));
  REQUIRE(true == is_multiplication_safe(-2, 2));
  REQUIRE(true == is_multiplication_safe(-3, 2));
  REQUIRE(true == is_multiplication_safe(-6, 2));
  REQUIRE(true == is_multiplication_safe(-6, 8));
  
  REQUIRE(true == is_multiplication_safe(1, -2));
  REQUIRE(true == is_multiplication_safe(2, -2));
  REQUIRE(true == is_multiplication_safe(3, -2));
  REQUIRE(true == is_multiplication_safe(6, -2));
  REQUIRE(true == is_multiplication_safe(6, -8));
  
  REQUIRE(true == is_multiplication_safe(-1, -2));
  REQUIRE(true == is_multiplication_safe(-2, -2));
  REQUIRE(true == is_multiplication_safe(-3, -2));
  REQUIRE(true == is_multiplication_safe(-6, -2));
  REQUIRE(true == is_multiplication_safe(-6, -8));
}

TEST_CASE("is_multiplcation_safe() for signed values returns false if multiplication op is unsafe") {
  using namespace iron::numeric;
  
  REQUIRE(false == is_multiplication_safe(12_i8, 11_i8)); // 132
  REQUIRE(false == is_multiplication_safe(13_i8, 10_i8)); // 130
  REQUIRE(false == is_multiplication_safe(16_i8, 16_i8)); // 256
  REQUIRE(false == is_multiplication_safe(17_i8, 16_i8)); // 272
  REQUIRE(false == is_multiplication_safe(63_i8, 63_i8));
  REQUIRE(false == is_multiplication_safe(64_i8, 63_i8));
  REQUIRE(false == is_multiplication_safe(64_i8, 64_i8));
}