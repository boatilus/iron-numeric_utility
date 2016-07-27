#include <limits>

#include "../deps/catch.h"
#include "../utility.h"


TEST_CASE("smallest_integer should yield type satisfying the contraints") {
  using namespace iron;

  constexpr auto int8_min   { std::numeric_limits<int8_t>::min() };
  constexpr auto int16_min  { std::numeric_limits<int16_t>::min() };
  constexpr auto int32_min  { std::numeric_limits<int32_t>::min() };
  constexpr auto int64_min  { std::numeric_limits<int64_t>::min() };
  constexpr auto int8_max   { std::numeric_limits<int8_t>::max() };
  constexpr auto int16_max  { std::numeric_limits<int16_t>::max() };
  constexpr auto int32_max  { std::numeric_limits<int32_t>::max() };
  constexpr auto int64_max  { std::numeric_limits<int64_t>::max() };

  constexpr auto uint8_max  { std::numeric_limits<uint8_t>::max() };
  constexpr auto uint16_max { std::numeric_limits<uint16_t>::max() };
  constexpr auto uint32_max { std::numeric_limits<uint32_t>::max() };
  constexpr auto uint64_max { std::numeric_limits<uint64_t>::max() };

  REQUIRE((std::is_same<int8_t, smallest_integer<int8_min, int8_max>::type>::value));
  REQUIRE((std::is_same<int16_t, smallest_integer<int16_min, int16_max>::type>::value));
  REQUIRE((std::is_same<int32_t, smallest_integer<int32_min, int32_max>::type>::value));
  REQUIRE((std::is_same<int64_t, smallest_integer<int64_min, int64_max>::type>::value));

  REQUIRE((std::is_same<uint8_t, smallest_integer<0, uint8_max>::type>::value));
  REQUIRE((std::is_same<uint16_t, smallest_integer<0, uint16_max>::type>::value));
  REQUIRE((std::is_same<uint32_t, smallest_integer<0, uint32_max>::type>::value));
  REQUIRE((std::is_same<uint64_t, smallest_integer<0, uint64_max>::type>::value));

  // TODO: generate random integers with which to test
}

TEST_CASE("smallest_integer_t should be of the correct type for given parameters") {
  using namespace iron;

  constexpr auto int8_min   { std::numeric_limits<int8_t>::min() };
  constexpr auto int16_min  { std::numeric_limits<int16_t>::min() };
  constexpr auto int32_min  { std::numeric_limits<int32_t>::min() };
  constexpr auto int64_min  { std::numeric_limits<int64_t>::min() };
  constexpr auto int8_max   { std::numeric_limits<int8_t>::max() };
  constexpr auto int16_max  { std::numeric_limits<int16_t>::max() };
  constexpr auto int32_max  { std::numeric_limits<int32_t>::max() };
  constexpr auto int64_max  { std::numeric_limits<int64_t>::max() };

  constexpr auto uint8_max  { std::numeric_limits<uint8_t>::max() };
  constexpr auto uint16_max { std::numeric_limits<uint16_t>::max() };
  constexpr auto uint32_max { std::numeric_limits<uint32_t>::max() };
  constexpr auto uint64_max { std::numeric_limits<uint64_t>::max() };

  REQUIRE((std::is_same<int8_t, smallest_integer_t<int8_min, int8_max>>::value));
  REQUIRE((std::is_same<int16_t, smallest_integer_t<int16_min, int16_max>>::value));
  REQUIRE((std::is_same<int32_t, smallest_integer_t<int32_min, int32_max>>::value));
  REQUIRE((std::is_same<int64_t, smallest_integer_t<int64_min, int64_max>>::value));

  REQUIRE((std::is_same<uint8_t, smallest_integer_t<0, uint8_max>>::value));
  REQUIRE((std::is_same<uint16_t, smallest_integer_t<0, uint16_max>>::value));
  REQUIRE((std::is_same<uint32_t, smallest_integer_t<0, uint32_max>>::value));
  REQUIRE((std::is_same<uint64_t, smallest_integer_t<0, uint64_max>>::value));
}