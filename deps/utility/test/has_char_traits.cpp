#include <string>

#include "../utility.h"

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "../deps/catch.h"


TEST_CASE("has_char_traits sets true value for std::string") {
  using namespace iron;
  
  REQUIRE((has_char_traits<std::string, std::char_traits<char>>::value));
}