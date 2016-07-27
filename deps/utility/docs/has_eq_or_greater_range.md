# `has_eq_or_greater_range<T, U>`

The `has_eq_or_greater_range` trait is templated on two parameters — `T` and `U` — and sets the trait's boolean `value` member to `true` if `T` has equal or greater integral range than `U`, where "integral range" is defined as the minimum and minimum values representable by the data type.

## Basic Usage

```c++
constexpr bool truthy { iron::has_eq_or_greater_range<int64_t, int32_t>::value }; // true
constexpr bool truthy { iron::has_eq_or_greater_range<int32_t, int32_t>::value }; // true
constexpr bool falsey { iron::has_eq_or_greater_range<int32_t, int16_t>::value }; // false
```

### Use Cases

`has_eq_or_greater_range` is useful in SFINAE where type `T` must be sufficient to hold the value of any type `U`. A simple albeit terribly pointless example of which being:

```c++
template <typename T, typename U>
std::enable_if_t<iron::has_eq_or_greater_range<T, U>::value, T> some_func(T a, T b) {
  a = b;  // No possible precision loss

  // Do other stuff...

  return a;
}
```