#include <string>

#include "../numeric_utility.h"

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "../deps/catch.h"


TEST_CASE("has_positive returns all correct results") {
  using namespace iron::numeric;

  REQUIRE(is_positive(3));
}