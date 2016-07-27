#include "../deps/catch.h"
#include "../utility.h"


TEST_CASE("has_samed_signedness returns true for same-signed ints") {
  using namespace iron;

  REQUIRE((have_same_signedness<int8_t, int8_t>::value));
  REQUIRE((have_same_signedness<int8_t, int16_t>::value));
  REQUIRE((have_same_signedness<int8_t, int32_t>::value));
  REQUIRE((have_same_signedness<int8_t, int64_t>::value));
  REQUIRE((have_same_signedness<int16_t, int8_t>::value));
  REQUIRE((have_same_signedness<int16_t, int16_t>::value));
  REQUIRE((have_same_signedness<int16_t, int32_t>::value));
  REQUIRE((have_same_signedness<int16_t, int64_t>::value));
  REQUIRE((have_same_signedness<int32_t, int8_t>::value));
  REQUIRE((have_same_signedness<int32_t, int16_t>::value));
  REQUIRE((have_same_signedness<int32_t, int32_t>::value));
  REQUIRE((have_same_signedness<int32_t, int64_t>::value));
  REQUIRE((have_same_signedness<int64_t, int8_t>::value));
  REQUIRE((have_same_signedness<int64_t, int16_t>::value));
  REQUIRE((have_same_signedness<int64_t, int32_t>::value));
  REQUIRE((have_same_signedness<int64_t, int64_t>::value));

  REQUIRE((have_same_signedness<uint8_t, uint8_t>::value));
  REQUIRE((have_same_signedness<uint8_t, uint16_t>::value));
  REQUIRE((have_same_signedness<uint8_t, uint32_t>::value));
  REQUIRE((have_same_signedness<uint8_t, uint64_t>::value));
  REQUIRE((have_same_signedness<uint16_t, uint8_t>::value));
  REQUIRE((have_same_signedness<uint16_t, uint16_t>::value));
  REQUIRE((have_same_signedness<uint16_t, uint32_t>::value));
  REQUIRE((have_same_signedness<uint16_t, uint64_t>::value));
  REQUIRE((have_same_signedness<uint32_t, uint8_t>::value));
  REQUIRE((have_same_signedness<uint32_t, uint16_t>::value));
  REQUIRE((have_same_signedness<uint32_t, uint32_t>::value));
  REQUIRE((have_same_signedness<uint32_t, uint64_t>::value));
  REQUIRE((have_same_signedness<uint64_t, uint8_t>::value));
  REQUIRE((have_same_signedness<uint64_t, uint16_t>::value));
  REQUIRE((have_same_signedness<uint64_t, uint32_t>::value));
  REQUIRE((have_same_signedness<uint64_t, uint64_t>::value));
}

TEST_CASE("has_samed_signedness returns false for differently-signed ints") {
  using namespace iron;

  REQUIRE(!(have_same_signedness<int8_t, uint8_t>::value));
  REQUIRE(!(have_same_signedness<int8_t, uint16_t>::value));
  REQUIRE(!(have_same_signedness<int8_t, uint32_t>::value));
  REQUIRE(!(have_same_signedness<int8_t, uint64_t>::value));
  REQUIRE(!(have_same_signedness<int16_t, uint8_t>::value));
  REQUIRE(!(have_same_signedness<int16_t, uint16_t>::value));
  REQUIRE(!(have_same_signedness<int16_t, uint32_t>::value));
  REQUIRE(!(have_same_signedness<int16_t, uint64_t>::value));
  REQUIRE(!(have_same_signedness<int32_t, uint8_t>::value));
  REQUIRE(!(have_same_signedness<int32_t, uint16_t>::value));
  REQUIRE(!(have_same_signedness<int32_t, uint32_t>::value));
  REQUIRE(!(have_same_signedness<int32_t, uint64_t>::value));
  REQUIRE(!(have_same_signedness<int64_t, uint8_t>::value));
  REQUIRE(!(have_same_signedness<int64_t, uint16_t>::value));
  REQUIRE(!(have_same_signedness<int64_t, uint32_t>::value));
  REQUIRE(!(have_same_signedness<int64_t, uint64_t>::value));

  REQUIRE(!(have_same_signedness<uint8_t, int8_t>::value));
  REQUIRE(!(have_same_signedness<uint8_t, int16_t>::value));
  REQUIRE(!(have_same_signedness<uint8_t, int32_t>::value));
  REQUIRE(!(have_same_signedness<uint8_t, int64_t>::value));
  REQUIRE(!(have_same_signedness<uint16_t, int8_t>::value));
  REQUIRE(!(have_same_signedness<uint16_t, int16_t>::value));
  REQUIRE(!(have_same_signedness<uint16_t, int32_t>::value));
  REQUIRE(!(have_same_signedness<uint16_t, int64_t>::value));
  REQUIRE(!(have_same_signedness<uint32_t, int8_t>::value));
  REQUIRE(!(have_same_signedness<uint32_t, int16_t>::value));
  REQUIRE(!(have_same_signedness<uint32_t, int32_t>::value));
  REQUIRE(!(have_same_signedness<uint32_t, int64_t>::value));
  REQUIRE(!(have_same_signedness<uint64_t, int8_t>::value));
  REQUIRE(!(have_same_signedness<uint64_t, int16_t>::value));
  REQUIRE(!(have_same_signedness<uint64_t, int32_t>::value));
  REQUIRE(!(have_same_signedness<uint64_t, int64_t>::value));
}
