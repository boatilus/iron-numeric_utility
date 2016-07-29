#include "../numeric_utility.h"
#include "../deps/catch.h"


TEST_CASE("to_positive() returns all correct results given valid arguments") {
  using namespace iron::numeric;
  
  static_assert(3 == to_positive(-3), "to_positive() should be constexpr callable");
  
  REQUIRE(1 == to_positive(-1));
  REQUIRE(3 == to_positive(-3));
  REQUIRE(std::numeric_limits<int8_t>::max() == (to_positive(std::numeric_limits<int8_t>::min() + 1)));
  REQUIRE(std::numeric_limits<int16_t>::max() == (to_positive(std::numeric_limits<int16_t>::min() + 1)));
  REQUIRE(std::numeric_limits<int32_t>::max() == (to_positive(std::numeric_limits<int32_t>::min() + 1)));
  REQUIRE(std::numeric_limits<int64_t>::max() == (to_positive(std::numeric_limits<int64_t>::min() + 1)));
}

TEST_CASE("to_postive() with any <int>::min() should throw") {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-value"
  
  try {
    iron::numeric::to_positive(std::numeric_limits<int8_t>::min());
  } catch (std::exception& e) {
    REQUIRE(e.what());
  }
  
  try {
    iron::numeric::to_positive(std::numeric_limits<int16_t>::min());
  } catch (std::exception& e) {
    REQUIRE(e.what());
  }
  
  try {
    iron::numeric::to_positive(std::numeric_limits<int32_t>::min());
  } catch (std::exception& e) {
    REQUIRE(e.what());
  }
  
  try {
    iron::numeric::to_positive(std::numeric_limits<int64_t>::min());
  } catch (std::exception& e) {
    REQUIRE(e.what());
  }
  
#pragma clang diagnostic pop
}