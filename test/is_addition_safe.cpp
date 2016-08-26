#include <future>
#include <iostream>

#include "../deps/catch.h"
#include "../numeric_utility.h"


TEST_CASE("is_addition_safe() for signed values returns true if addition op is safe") {
  using namespace iron::numeric;

  static_assert(
    true == is_addition_safe(3, 6),
    "is_addition_safe() for signed values should be constexpr-callable"
  );
  
  REQUIRE(true == is_addition_safe(0, 0));
  
  for (size_t i = 0; i < static_cast<size_t>(std::numeric_limits<int8_t>::max()); ++i) {
    CHECK(true == is_addition_safe(0, i));
  }
  
  REQUIRE(true == is_addition_safe(std::numeric_limits<int8_t>::max(), 0));
  REQUIRE(true == is_addition_safe(std::numeric_limits<int16_t>::max(), 0));
  REQUIRE(true == is_addition_safe(std::numeric_limits<int32_t>::max(), 0));
  REQUIRE(true == is_addition_safe(std::numeric_limits<int64_t>::max(), 0));
}

TEST_CASE("is_addition_safe() for signed values returns false if addition op is unsafe") {
  using namespace iron::numeric;
  
  {
    using t = int8_t;
  
	for (size_t i = 1; i < (static_cast<size_t>(std::numeric_limits<t>::max()) * 2ull); ++i) {
      CHECK(false == is_addition_safe(std::numeric_limits<t>::max(), i));
    }
  };
  
  {
    using t = int16_t;
    
    for (size_t i = 1; i < static_cast<size_t>(std::numeric_limits<t>::max()); ++i) {
      CHECK(false == is_addition_safe(std::numeric_limits<t>::max(), i));
    }
  }
}

TEST_CASE("is_addition_safe() for unsigned values returns true if addition op is safe") {
  using namespace iron::numeric;
  
  static_assert(
    true == is_addition_safe(static_cast<unsigned int>(3), 6),
    "is_addition_safe() for unsigned values should be constexpr-callable"
  );
  
  REQUIRE(true == is_addition_safe(static_cast<unsigned int>(0), 0));
  
  REQUIRE(true == is_addition_safe(std::numeric_limits<uint8_t>::max(), 0));
  REQUIRE(true == is_addition_safe(std::numeric_limits<uint16_t>::max(), 0));
  REQUIRE(true == is_addition_safe(std::numeric_limits<uint32_t>::max(), 0));
  REQUIRE(true == is_addition_safe(std::numeric_limits<uint64_t>::max(), 0));
  
  {
    using t = uint8_t;
    
    for (size_t i = 1; i < (static_cast<size_t>(std::numeric_limits<t>::max()) * 2); ++i) {
      CHECK(false == is_addition_safe(std::numeric_limits<t>::max(), i));
    }
  }
  
  {
    using t = uint16_t;
    
    for (size_t i = 1; i < (static_cast<size_t>(std::numeric_limits<t>::max()) * 2); ++i) {
      CHECK(false == is_addition_safe(std::numeric_limits<t>::max(), i));
    }
  }
}