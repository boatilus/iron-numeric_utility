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
#include <type_traits>


namespace iron {  
  //////////////////////////
  // Integral type traits //
  //////////////////////////

  template <typename T, typename U>
  struct have_same_signedness {
    static const bool value {
         (std::is_signed<T>::value && std::is_signed<U>::value)
      || (std::is_unsigned<T>::value && std::is_unsigned<U>::value)
    };
  };


  template <typename T> struct is_integer_like { static const bool value { false }; };
  template <> struct is_integer_like<int8_t>   { static const bool value { true }; };
  template <> struct is_integer_like<int16_t>  { static const bool value { true }; };
  template <> struct is_integer_like<int32_t>  { static const bool value { true }; };
  template <> struct is_integer_like<int64_t>  { static const bool value { true }; };
  template <> struct is_integer_like<uint8_t>  { static const bool value { true }; };
  template <> struct is_integer_like<uint16_t> { static const bool value { true }; };
  template <> struct is_integer_like<uint32_t> { static const bool value { true }; };
  template <> struct is_integer_like<uint64_t> { static const bool value { true }; };
  
  
  // For any integer types `T` and `U`, if the minimum and maximum values of `T` are
  // greater than those of `U`, the boolean `::value` will be `true`
  template <typename T, typename U>
  struct has_eq_or_greater_range {
    static const bool value {
         std::numeric_limits<T>::min() <= std::numeric_limits<U>::min()
      && std::numeric_limits<T>::max() >= std::numeric_limits<U>::max()
    };
  };


  template <typename T, typename U>
  struct has_equivalent_range {
    static const bool value {
         std::numeric_limits<T>::min() <= std::numeric_limits<U>::min()
      && std::numeric_limits<T>::max() >= std::numeric_limits<U>::max()
    };
  };
  
  
  // Given an integral `width` (number of bits), return the associated integer type with the
  // width equal to `width`
  template <int width> struct width_as_integer;
  template <> struct width_as_integer<8>  { using type = int8_t; };
  template <> struct width_as_integer<16> { using type = int16_t; };
  template <> struct width_as_integer<32> { using type = int32_t; };
  template <> struct width_as_integer<64> { using type = int64_t; };

  // Given an integral `width` (number of bits), return the associated unsigned integer type with the
  // width equal to `width`
  template <int width> struct width_as_uinteger;
  template <> struct width_as_uinteger<8>  { using type = uint8_t; };
  template <> struct width_as_uinteger<16> { using type = uint16_t; };
  template <> struct width_as_uinteger<32> { using type = uint32_t; };
  template <> struct width_as_uinteger<64> { using type = uint64_t; };
  
  template <int width> struct width_as_floating_point;
  template <> struct width_as_floating_point<32> { using type = float; };
  template <> struct width_as_floating_point<64> { using type = double; };

  template <int width> using width_as_integer_t         = typename width_as_integer<width>::type;
  template <int width> using width_as_uinteger_t        = typename width_as_uinteger<width>::type;
  template <int width> using width_as_floating_point_t  = typename width_as_floating_point<width>::type;
  
  
  // Given an unsigned integral type `T`, `::type` will be equal to signed integer type capable of
  // representing T_MAX
  template <typename T> struct safe_to_int {};
  template <> struct safe_to_int<uint8_t>   { using type = int16_t; };
  template <> struct safe_to_int<uint16_t>  { using type = int32_t; };
  template <> struct safe_to_int<uint32_t>  { using type = int64_t; };
  
  
  ///////////////////////////
  // Smallest integer type //
  ///////////////////////////
  
  // Given a range [`low`, `high`], find the smallest signed or unsigned integer type in which both
  // `low` and `high` will fit
  template <intmax_t low, uintmax_t high, typename is_unsigned = void>
  struct smallest_integer;

  // if `low` is < `0`, `::type` should be the smallest signed type in which both `low` and `high`
  // will fit
  template <intmax_t low, uintmax_t high>
  struct smallest_integer<
    low,
    high,
    std::enable_if_t<(low < 0) && (high <= static_cast<uintmax_t>(std::numeric_limits<intmax_t>::max()))>
  > {
    static const int low_min_width {
      low >= std::numeric_limits<int8_t>::min()  ? 8  :
      low >= std::numeric_limits<int16_t>::min() ? 16 :
      low >= std::numeric_limits<int32_t>::min() ? 32 :
                                                   64 };
    
    static const int high_min_width {
      high <= std::numeric_limits<int8_t>::max()  ? 8  :
      high <= std::numeric_limits<int16_t>::max() ? 16 :
      high <= std::numeric_limits<int32_t>::max() ? 32 :
                                                    64 };
    
    using type = width_as_integer_t<high_min_width >= low_min_width ? high_min_width : low_min_width>;
  };

  // if `low` is >= `0`, `::type` should be the smallest unsigned type in which `high` will fit
  template <intmax_t low, uintmax_t high>
  struct smallest_integer<low, high, std::enable_if_t<(low >= 0)>> {
    static const int high_min_width {
      high <= std::numeric_limits<uint8_t>::max()  ? 8  :
      high <= std::numeric_limits<uint16_t>::max() ? 16 :
      high <= std::numeric_limits<uint32_t>::max() ? 32 :
                                                     64 };
    
    using type = width_as_uinteger_t<high_min_width>;
  };
  
  // smallest_integer<>::type helper
  template <intmax_t low, uintmax_t high>
  using smallest_integer_t = typename smallest_integer<low, high>::type;
  
  
  /////////////////////////
  // char_traits helpers //
  /////////////////////////
  
  template <typename T, typename traits>
  struct has_char_traits {
    static const bool value { std::is_same<typename T::traits_type, traits>::value };
  };


  template <typename T, typename U>
  struct has_same_char_traits {
    static const bool value { std::is_same<typename T::traits_type, typename U::traits_type>::value };
  };
  
  
  // `enable_if` type that ensures `T` has a `traits_type` type == `traits` argument
  template <typename T, typename traits, typename V = void>
  using has_char_traits_t = typename std::enable_if<
    std::is_same<typename T::traits_type, traits>::value, V
  >::type;


  // `enable_if` type that ensures `T` and `U` have the same `traits_type` type
  template <typename T, typename U, typename V = void>
  using has_same_char_traits_t = typename std::enable_if<
    std::is_same<typename T::traits_type, typename U::traits_type>::value, V
  >::type;


   /////////////////////////////////
  // Variadic type_trait similes //
  /////////////////////////////////
  
  template <typename... Ts>
  struct all_arithmetic;
  
  template <typename T>
  struct all_arithmetic<T> { static const auto value { std::is_arithmetic<T>::value }; };

  template <typename T, typename... Ts>
  struct all_arithmetic<T, Ts...> {
    static const auto value { std::is_arithmetic<T>::value && all_arithmetic<Ts...>::value };
  };
  
  
  template <typename... Ts>
  struct all_integral;
  
  template <typename T>
  struct all_integral<T> { static const auto value { std::is_integral<T>::value }; };

  template <typename T, typename... Ts>
  struct all_integral<T, Ts...> {
    static const auto value = std::is_integral<T>::value && all_integral<Ts...>::value;
  };
  

  template <typename... Ts>
  struct all_signed;
  
  template <typename T>
  struct all_signed<T> { static const auto value { std::is_signed<T>::value }; };

  template <typename T, typename... Ts>
  struct all_signed<T, Ts...> {
    static const auto value = std::is_signed<T>::value && all_signed<Ts...>::value;
  };
  
  
  template <typename... Ts>
  struct all_unsigned;
  
  template <typename T>
  struct all_unsigned<T> { static const bool value { std::is_unsigned<T>::value }; };

  template <typename T, typename... Ts>
  struct all_unsigned<T, Ts...> {
    static const bool value { std::is_unsigned<T>::value && all_unsigned<Ts...>::value };
  };
  
  
  template <typename... Ts>
  struct all_floating_point;
  
  template <typename T>
  struct all_floating_point<T> { static const bool value { std::is_floating_point<T>::value }; };

  template <typename T, typename... Ts>
  struct all_floating_point<T, Ts...> {
    static const bool value { std::is_floating_point<T>::value && all_floating_point<Ts...>::value };
  };
  
  
  //////////////////////////////
  // enable_if shortcut types //
  //////////////////////////////

  template <typename T, typename V = void>
  using is_pointer_t = typename std::enable_if<std::is_pointer<T>::value, V>::type;

  template <typename T, typename V = void>
  using is_class_t = typename std::enable_if<std::is_class<T>::value, V>::type;

  template <typename T, typename V = void>
  using is_integral_t = typename std::enable_if<std::is_integral<T>::value, V>::type;

  template <typename T, typename V = void>
  using is_signed_t = typename std::enable_if<std::is_signed<T>::value, V>::type;

  template <typename T, typename V = void>
  using is_unsigned_t = typename std::enable_if<std::is_unsigned<T>::value, V>::type;
  
  template <typename T>
  using make_unsigned_t = typename std::make_unsigned<T>::type;
}