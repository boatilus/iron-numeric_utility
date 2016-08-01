#include "../numeric_utility.h"
#include <iostream>

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "../deps/catch.h"


TEST_CASE("clamp() returns all correct results") {
  using namespace iron::numeric;

  static_assert(clamp(3, 0, 10), "clamp() should be constexpr-callable");
  
  REQUIRE(3 == clamp(3, 0, 10));
  REQUIRE(0 == clamp(-4, 0, 10));
  REQUIRE(10 == clamp(12, 0, 10));
  
  REQUIRE(8 == clamp(247, 8, 8));
  
  REQUIRE(-3 == clamp(-3, static_cast<int64_t>(-1000), static_cast<int64_t>(300)));
}

TEST_CASE("clamp() with lower > upper should throw") {
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-value"
#endif
  using namespace iron::numeric;
  
  try {
    clamp(247, 8, 7);
  } catch (std::exception& e) {
    REQUIRE(e.what());
  }
  
#ifdef __clang__
#pragma clang diagnostic pop
#endif
}