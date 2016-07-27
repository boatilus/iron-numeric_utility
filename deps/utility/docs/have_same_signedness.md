# `have_same_signedness<T, U>`

The `have_same_signedness` trait is templated on two parameters — `T` and `U` — and sets the trait's boolean `value` member to `true` if both `T` and `U` are *both* unsigned **or** are *both* signed.

## Basic Usage

```c++
constexpr bool truthy { iron::have_same_signedness<int, long>::value };           // true
constexpr bool falsey { iron::have_same_signedness<unsigned int, short>::value }; // false
```

### Use Cases

`have_same_signedness` is useful in SFINAE in which you desire that only same-signed types be allowed. E.g.,

```c++
template <typename T, typename U>
std::enable_if_t<iron::have_same_signedness<T, U>::value, void> some_func(T a, T b) {}
```