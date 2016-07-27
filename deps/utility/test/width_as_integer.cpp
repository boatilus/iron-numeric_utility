#include "../deps/catch.h"
#include "../utility.h"


TEST_CASE("width_as_integer offers the correct type") {
  using namespace iron;
  
  REQUIRE((std::is_same<int8_t, width_as_integer<8>::type>::value));
  REQUIRE((std::is_same<int16_t, width_as_integer<16>::type>::value));
  REQUIRE((std::is_same<int32_t, width_as_integer<32>::type>::value));
  REQUIRE((std::is_same<int64_t, width_as_integer<64>::type>::value));
}

TEST_CASE("width_as_uninteger offers the correct type") {
  using namespace iron;
  
  REQUIRE((std::is_same<uint8_t, width_as_uinteger<8>::type>::value));
  REQUIRE((std::is_same<uint16_t, width_as_uinteger<16>::type>::value));
  REQUIRE((std::is_same<uint32_t, width_as_uinteger<32>::type>::value));
  REQUIRE((std::is_same<uint64_t, width_as_uinteger<64>::type>::value));
}

TEST_CASE("width_as_floaitng_point offers the correct type") {
  using namespace iron;
  
  REQUIRE((std::is_same<float, width_as_floating_point<32>::type>::value));
  REQUIRE((std::is_same<double, width_as_floating_point<64>::type>::value));
}

TEST_CASE("width types yield the correct result") {
  using namespace iron;
  
  REQUIRE((std::is_same<int8_t, width_as_integer_t<8>>::value));
  REQUIRE((std::is_same<int16_t, width_as_integer_t<16>>::value));
  REQUIRE((std::is_same<int32_t, width_as_integer_t<32>>::value));
  REQUIRE((std::is_same<int64_t, width_as_integer_t<64>>::value));
  
  REQUIRE((std::is_same<uint8_t, width_as_uinteger_t<8>>::value));
  REQUIRE((std::is_same<uint16_t, width_as_uinteger_t<16>>::value));
  REQUIRE((std::is_same<uint32_t, width_as_uinteger_t<32>>::value));
  REQUIRE((std::is_same<uint64_t, width_as_uinteger_t<64>>::value));
  
  REQUIRE((std::is_same<float, width_as_floating_point_t<32>>::value));
  REQUIRE((std::is_same<double, width_as_floating_point_t<64>>::value));
}