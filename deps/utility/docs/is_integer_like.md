# `is_integer_like<T>`

The `is_integer_like` trait is parameterized on type `T`, and sets the boolean `value` member to `true` if `T` is "integer-like". In other words, if `T` is either a built-in integer or if it *behaves* as one.

The intent of `is_integer_like` is that it be specialized on user-defined wrapped integer types, or any type that is expected to behave similarly enough to the fundamental integer types to meet some arbitrary criteria for "integer-like".

## Basic Usage

```c++
constexpr bool truthy { iron::is_integer_like<int>::value };    // true
constexpr bool falsey { iron::is_integer_like<float>::value };  // false

struct wrapped_integer {
  int value;
}

template <> struct iron::is_integer_like<wrapped_integer> { static const bool value { true }; };

constexpr bool truthy { iron::is_integer_like<a>::value };  // true
```