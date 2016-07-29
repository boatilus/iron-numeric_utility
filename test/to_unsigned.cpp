#include "../numeric_utility.h"
#include "../deps/catch.h"


TEST_CASE("to_unsigned() returns all correct results given valid arguments") {
  using namespace iron::numeric;
  
  static_assert(3 == to_unsigned(3), "to_unsigned() should be constexpr-callable");
  
  constexpr int8_t  i8  { 0 };
  constexpr int16_t i16 { 8881 };
  constexpr int32_t i32 { std::numeric_limits<int32_t>::max() / 2 };
  constexpr int64_t i64 { std::numeric_limits<int64_t>::max() };
  
  REQUIRE((i8 == to_unsigned(i8) && (std::is_same<uint8_t, decltype(to_unsigned(i8))>::value)));
  REQUIRE((i16 == to_unsigned(i16) && (std::is_same<uint16_t, decltype(to_unsigned(i16))>::value)));
  REQUIRE((i32 == to_unsigned(i32) && (std::is_same<uint32_t, decltype(to_unsigned(i32))>::value)));
  REQUIRE((i64 == to_unsigned(i64) && (std::is_same<uint64_t, decltype(to_unsigned(i64))>::value)));
}

TEST_CASE("to_unsigned() with any negative value should throw") {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-value"
  using namespace iron::numeric;
  
  try {
    to_unsigned(-1);
  } catch (std::exception& e) {
    REQUIRE(e.what());
  }
  
  try {
    to_unsigned(std::numeric_limits<int32_t>::min());
  } catch (std::exception& e) {
    REQUIRE(e.what());
  }
  
#pragma clang diagnostic pop
}