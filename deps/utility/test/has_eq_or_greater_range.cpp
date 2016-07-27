#include "../deps/catch.h"
#include "../utility.h"


TEST_CASE("has_eq_or_greater range returns correct boolean") {
  using namespace iron;

  REQUIRE((has_eq_or_greater_range<int8_t, int8_t>::value));
  REQUIRE((has_eq_or_greater_range<int16_t, int8_t>::value));
  REQUIRE((has_eq_or_greater_range<int32_t, int8_t>::value));
  REQUIRE((has_eq_or_greater_range<int64_t, int8_t>::value));
  REQUIRE((has_eq_or_greater_range<int16_t, int16_t>::value));
  REQUIRE((has_eq_or_greater_range<int32_t, int16_t>::value));
  REQUIRE((has_eq_or_greater_range<int64_t, int16_t>::value));
  REQUIRE((has_eq_or_greater_range<int32_t, int32_t>::value));
  REQUIRE((has_eq_or_greater_range<int64_t, int32_t>::value));
  REQUIRE((has_eq_or_greater_range<int64_t, int64_t>::value));

  REQUIRE((has_eq_or_greater_range<uint8_t, uint8_t>::value));
  REQUIRE((has_eq_or_greater_range<uint16_t, uint8_t>::value));
  REQUIRE((has_eq_or_greater_range<uint32_t, uint8_t>::value));
  REQUIRE((has_eq_or_greater_range<uint64_t, uint8_t>::value));
  REQUIRE((has_eq_or_greater_range<uint16_t, uint16_t>::value));
  REQUIRE((has_eq_or_greater_range<uint32_t, uint16_t>::value));
  REQUIRE((has_eq_or_greater_range<uint64_t, uint16_t>::value));
  REQUIRE((has_eq_or_greater_range<uint32_t, uint32_t>::value));
  REQUIRE((has_eq_or_greater_range<uint64_t, uint32_t>::value));
  REQUIRE((has_eq_or_greater_range<uint64_t, uint64_t>::value));
}