/*
  CC0 1.0 Universal (CC0 1.0)
  Public Domain Dedication

  The person who associated a work with this deed has dedicated the work to the public domain by
  waiving all of his or her rights to the work worldwide under copyright law, including all related
  and neighboring rights, to the extent allowed by law.

  You can copy, modify, distribute and perform the work, even for commercial purposes, all without
  asking permission.

  https://creativecommons.org/publicdomain/zero/1.0/
*/


#pragma once

#include <cstdint>
#include <limits>
#include <stdexcept>
#include <type_traits>

#include "deps/utility/utility.h"

#if __clang__
#define attr_const __attribute__((const))
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wgcc-compat" // "GCC does not allow const attribute in this position..."
#else
#define attr_const
#endif


namespace iron {
  namespace numeric {
    //////////////////////
    // Integral signage //
    //////////////////////

    template <typename T>
    constexpr std::enable_if_t<std::is_integral<T>::value, bool> is_positive(
      T n
    ) noexcept attr_const {
      return n > 0;
    }

    // TODO
    template <typename T>
    constexpr std::enable_if_t<std::is_floating_point<T>::value, bool> is_positive(
      T n
    ) noexcept attr_const {
      return n;
    }

    template <typename T>
    constexpr std::enable_if_t<std::is_integral<T>::value, bool> is_negative(
      T n
    ) noexcept attr_const {
      return n < 0;
    }

    template <typename T>
    constexpr std::enable_if_t<std::is_signed<T>::value, T> to_positive(
      T n
    ) attr_const {
      if (std::numeric_limits<T>::min() == n) {
        throw std::range_error("insufficient range to cast to a positive value");
      }
    
      return n > 0 ? n : -(n);
    }

    // TODO
    template <typename T>
    constexpr std::enable_if_t<std::is_floating_point<T>::value, T> to_positive(
      T n
    ) noexcept attr_const {
      return n;
    }

    template <typename T>
    constexpr std::enable_if_t<std::is_integral<T>::value, T> to_negative(
      T n
    ) noexcept attr_const {
      return n < 0 ? n : -(n);
    }


    // Safely converts from signed to unsigned for all signed types
    template <typename T>
    constexpr auto to_unsigned(T n)
      -> std::enable_if_t<std::is_signed<T>::value, std::make_unsigned_t<T>>
    {
      if (0 <= n) {
        return static_cast<std::make_unsigned_t<T>>(n);
      } else {
        throw std::range_error("conversion of negative value to unsigned is unsafe");
      }
    }

    
    // Safely converts from unsigned to signed for all cases except `uint64_t`
    constexpr auto to_signed(uint8_t n) noexcept attr_const { return static_cast<int16_t>(n); }
    constexpr auto to_signed(uint16_t n) noexcept attr_const { return static_cast<int32_t>(n); }
    constexpr auto to_signed(uint32_t n) noexcept attr_const { return static_cast<int64_t>(n); }
    
    constexpr auto to_signed(uint64_t n) attr_const {
      return static_cast<uint64_t>(std::numeric_limits<int64_t>::max()) >= n
        ? static_cast<int64_t>(n)
        : throw std::range_error("conversion of signed value to unsigned is unsafe");
    }
    
    /*
    // Safely converts from unsigned to signed for all cases except `uint64_t`
    template <typename T>
    constexpr auto to_signed(T n) noexcept
      -> std::enable_if_t<std::is_unsigned<T>::value, typename safe_to_int<T>::type>
    {
      return static_cast<typename safe_to_int<T>::type>(n);
    }
    */
    

    /////////////////////
    // Integral bounds //
    /////////////////////

    // Clamps an integer within [`lower`, `upper`]
    /*
    template <typename T>
    constexpr std::enable_if_t<std::is_integral<T>::value, T> clamp(
      T n, T lower, T upper
    ) attr_const {
      if (lower > upper) {
        throw std::invalid_argument("lower bound mustn't be greater than upper bound");
      }
    
      if (n < lower) {
        return lower;
      } else if (n > upper) {
        return upper;
      } else {
        return n;
      }
    }
    */
    
    // Clamps an integer within [`lower`, `upper`], throwing exception if `lower`'s not less than or
    // equal to `upper`
    namespace internal {
      template <typename T, typename U>
      constexpr void check_clamp_range(T lower, U upper) {
        lower > upper
          ? throw std::invalid_argument("lower bound must not be greater than upper bound")
          : 0;
      }
    }
    
    
    template <typename T, typename LT, typename UT>
    constexpr std::enable_if_t<all_integral<T, LT, UT>::value, T> clamp(T n, LT lower, UT upper) {
      internal::check_clamp_range(lower, upper);
    
      if (n < lower) {
        return static_cast<T>(lower);
      } else if (n > upper) {
        return static_cast<T>(upper);
      } else {
        return n;
      }
    }
    
    
    // Clamps an integer within [`lower`, `upper]
    template <typename T, T lower, T upper>
    constexpr std::enable_if_t<std::is_integral<T>::value && (upper >= lower), T> restrict_within(
      const T n
    ) noexcept attr_const {
      if (n < lower) {
        return lower;
      } else if (n > upper) {
        return upper;
      } else {
        return n;
      }
    }


    // Return value if within [`min`, `max`], else throw `std::out_of_range`
    template <typename T>
    constexpr std::enable_if_t<std::is_integral<T>::value, T> check_range(
      T n, T lower, T upper
    ) {
      if ((n >= lower) && (n <= upper)) {
        return n;
      } else {
        throw std::out_of_range("value not within range");
      }
    }


    /////////////////////////////
    // Integral safe operation //
    /////////////////////////////
  
    // Addition
    template <typename T, typename U>
    constexpr std::enable_if_t<
      std::is_signed<T>::value && std::is_integral<U>::value, bool
    > is_addition_safe(T lhs, U rhs) noexcept attr_const {
      if (std::numeric_limits<T>::max() < static_cast<intmax_t>(rhs)) return false;
      
      const auto _rhs { static_cast<T>(rhs) };
    
      return
        ((_rhs > 0) && (lhs > (std::numeric_limits<T>::max() - _rhs))) ||
        ((_rhs < 0) && (lhs < (std::numeric_limits<T>::min() - _rhs)))
        ? false
        : true;
    }

    template <typename T, typename U>
    constexpr std::enable_if_t<
      std::is_unsigned<T>::value && std::is_integral<U>::value, bool
    > is_addition_safe(T lhs, U rhs) noexcept attr_const {
      if (std::numeric_limits<T>::max() < static_cast<uintmax_t>(rhs)) return false;
    
      return lhs > (std::numeric_limits<T>::max() - static_cast<T>(rhs)) ? false : true;
    }


    // Subtraction
    template <typename T>
    constexpr std::enable_if_t<std::is_signed<T>::value, bool> is_subtraction_safe(
      T lhs, T rhs
    ) noexcept attr_const {
      return
        ((rhs > 0) && (lhs < (std::numeric_limits<T>::min() + rhs))) ||
        ((rhs < 0) && (lhs > (std::numeric_limits<T>::max() + rhs)))
        ? false
        : true;
    }

    template <typename T>
    constexpr std::enable_if_t<std::is_unsigned<T>::value, bool> is_subtraction_safe(
      T lhs, T rhs
    ) noexcept attr_const {
      return lhs < rhs ? false : true;
    }


    // Multiplication
    template <typename T>
    constexpr std::enable_if_t<std::is_signed<T>::value, bool> is_multiplication_safe(
      T lhs, T rhs
    ) noexcept attr_const {
      return
        to_positive(lhs) >(std::numeric_limits<T>::max() / to_positive(rhs))
        ? false
        : true;
    }

    template <typename T>
    constexpr std::enable_if_t<std::is_unsigned<T>::value, bool> is_multiplication_safe(
      T lhs, T rhs
    ) noexcept attr_const {
      return lhs > (std::numeric_limits<T>::max() / rhs) ? false : true;
    }


    // Division
    template <typename T>
    constexpr std::enable_if_t<std::is_signed<T>::value, bool> is_division_safe(
      T lhs, T rhs
    ) noexcept attr_const {
      return
        (0 == rhs) || ((std::numeric_limits<T>::min() == lhs) && (-1 == rhs))
        ? false
        : true;
    }

    template <typename T>
    constexpr std::enable_if_t<std::is_unsigned<T>::value, bool> is_division_safe(
      T lhs, T rhs
    ) noexcept attr_const {
      return (0 == rhs) || (0 == lhs) ? false : true;
    }


    // Modulo
    template <typename T>
    constexpr std::enable_if_t<std::is_integral<T>::value, bool> is_modulo_safe(
      T lhs, T rhs
    ) noexcept attr_const {
      return is_division_safe(lhs, rhs);
    }


    // Left shift
    template <typename T>
    constexpr std::enable_if_t<std::is_signed<T>::value, bool> is_left_shift_safe(
      T lhs, T rhs
    ) noexcept attr_const {
      return
        (lhs < 0) ||
        (rhs < 0) ||
        (rhs >= std::numeric_limits<unsigned long long>::digits) ||
        (lhs >(std::numeric_limits<T>::max() >> rhs))
        ? false
        : true;
    }


    // Unary negation
    template <typename T>
    constexpr std::enable_if_t<std::is_signed<T>::value, bool> is_unary_negation_safe(
      T value
    ) noexcept attr_const {
      return std::numeric_limits<T>::min() == value ? false : true;
    }


    ////////////////////
    // Integral power //
    ////////////////////

    namespace internals {
      template <typename T>
      constexpr uint32_t power_helper(T base, T exponent, T sqrt) noexcept attr_const {
        return sqrt * sqrt * ((exponent % 2U) ? base : 1U);
      }
    }


    template <typename T>
    constexpr std::enable_if_t<std::is_signed<T>::value, uint32_t> power(
      T base, T exponent
    ) {
      return
        exponent > 0
        ? exponent == 0 ? 1 : internals::power_helper(base, exponent, power(base, exponent / 2))
        : throw std::range_error("negative exponent passed to power()");
    }

    template <typename T>
    constexpr std::enable_if_t<std::is_unsigned<T>::value, uint32_t> power(
      T base, T exponent
    ) {
      return
        exponent == 0U
        ? 1U
        : internals::power_helper(base, exponent, power(base, exponent / 2U));
    }


    /////////////////////
    // Integral digits //
    /////////////////////

    namespace internals {
      template <typename T>
      constexpr uint32_t num_digits_recursive(T n, uint32_t digits = 1U) noexcept attr_const;
    }


    // Computes the number of digits in an integer
    // Does less-than comparisons to 7 digits, then gives up and recurses
    template <typename T>
    constexpr std::enable_if_t<std::is_unsigned<T>::value, uint32_t> num_digits(
      T n
    ) noexcept attr_const {
      return  n < 10U ? 1U :
        n < 100U ? 2U :
        n < 1000U ? 3U :
        n < 10000U ? 4U :
        n < 100000U ? 5U :
        n < 1000000U ? 6U :
        n < 10000000U ? 7U :
        internals::num_digits_recursive(n, 8U);
    }

    template <typename T>
    constexpr std::enable_if_t<std::is_signed<T>::value, uint32_t> num_digits(
      T n
    ) noexcept attr_const {
      return num_digits(to_unsigned(to_positive(n)));
    }


    namespace internals {
      template <typename T>
      constexpr uint32_t num_digits_recursive(T n, uint32_t digits) noexcept attr_const {
        return n < power(10U, digits) ? digits : num_digits_recursive(n, digits + 1U);
      }
    }


    ///////////////////////
    // Integral rounding //
    ///////////////////////

    template <typename T>
    constexpr std::enable_if_t<std::is_integral<T>::value, T> round_up(
      T n, T multiple
    ) noexcept attr_const {
      return multiple != 0 ? ((n + multiple - 1) / multiple) * multiple : 0;
    }


    ///////////////////////////////////////////////////////////////////////
    // min                                                               //
    //                                                                   //
    // Similar to std::min, but allows comparisons between varying types //
    ///////////////////////////////////////////////////////////////////////

    template <typename T>
    constexpr __attribute__((const)) T min(T a, T b) noexcept { return a < b ? a : b; }

    template <typename T, typename U>
    constexpr __attribute__((const)) std::enable_if_t<
      (std::numeric_limits<T>::max() > std::numeric_limits<U>::max()),
      T
    > min(T a, U b) noexcept {
      return a < static_cast<T>(b) ? a : static_cast<T>(b);
    }

    template <typename T, typename U>
    constexpr __attribute__((const)) std::enable_if_t<
      (std::numeric_limits<U>::max() > std::numeric_limits<T>::max()),
      U
    > min(T a, U b) noexcept {
      return static_cast<U>(a) < b ? static_cast<U>(a) : b;
    }


    ///////////////////////////////////////////////////////////////////////
    // max                                                               //
    //                                                                   //
    // Similar to std::min, but allows comparisons between varying types //
    ///////////////////////////////////////////////////////////////////////

    template <typename T>
    constexpr __attribute__((const)) T max(T a, T b) noexcept { return a < b ? b : a; }

    template <typename T, typename U>
    constexpr __attribute__((const)) std::enable_if_t<
      (std::numeric_limits<T>::max() > std::numeric_limits<U>::max()),
      T
    > max(T a, U b) noexcept {
      return a < static_cast<T>(b) ? b : static_cast<T>(a);
    }

    template <typename T, typename U>
    constexpr __attribute__((const)) std::enable_if_t<
      (std::numeric_limits<U>::max() > std::numeric_limits<T>::max()),
      U
    > max(T a, U b) noexcept {
      return static_cast<U>(a) < b ? static_cast<U>(b) : a;
    }
  }
}


#ifdef attr_const
#undef attr_const
#endif

#if __clang__
#pragma clang diagnostic pop  // -Wgcc-compat
#endif
