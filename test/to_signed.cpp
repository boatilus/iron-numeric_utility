#include "../numeric_utility.h"
#include "../deps/catch.h"


TEST_CASE("to_signed() returns all correct results") {
  using namespace iron::numeric;
  
  constexpr uint8_t  u8  { 0 };
  constexpr uint16_t u16 { 8881 };
  constexpr uint32_t u32 { std::numeric_limits<uint32_t>::max() };
  constexpr uint64_t u64 { std::numeric_limits<int64_t>::max() };
  
  static_assert(u16 == to_signed(u16), "to_signed() should be constexpr callable");
  
  REQUIRE((u8 == to_signed(u8) && (std::is_same<int16_t, decltype(to_signed(u8))>::value)));
  REQUIRE((u16 == to_signed(u16) && (std::is_same<int32_t, decltype(to_signed(u16))>::value)));
  REQUIRE((u32 == to_signed(u32) && (std::is_same<int64_t, decltype(to_signed(u32))>::value)));
  REQUIRE((u64 == to_signed(u64) && (std::is_same<int64_t, decltype(to_signed(u64))>::value)));
}

TEST_CASE("to_signed() with a value exceeding INT64_MAX should throw") {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-value"
  using namespace iron::numeric;
  
  try {
    to_signed(static_cast<uint64_t>(std::numeric_limits<int64_t>::max() + 1));
  } catch (std::exception& e) {
    REQUIRE(e.what());
  }
  
#pragma clang diagnostic pop
}