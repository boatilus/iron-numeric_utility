#include <limits>

#include "../deps/catch.h"
#include "../utility.h"


TEST_CASE("safe_to_int yields the correct type for valid parameters") {
  using namespace iron;

  REQUIRE((std::is_same<int16_t, safe_to_int<uint8_t>::type>::value));
  REQUIRE((std::is_same<int32_t, safe_to_int<uint16_t>::type>::value));
  REQUIRE((std::is_same<int64_t, safe_to_int<uint32_t>::type>::value));
}

TEST_CASE("safe_to_int yields type satisfying design parameters") {
  using namespace iron;

  REQUIRE(
    std::numeric_limits<int16_t>::max() >= std::numeric_limits<safe_to_int<uint8_t>::type>::max()
  );

  REQUIRE(
    std::numeric_limits<int32_t>::max() >= std::numeric_limits<safe_to_int<uint16_t>::type>::max()
  );

  REQUIRE(
    std::numeric_limits<int64_t>::max() >= std::numeric_limits<safe_to_int<uint32_t>::type>::max()
  );
}