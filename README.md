# Decompose

A simple header-only library implementing [htjf's trick](https://www.reddit.com/r/cpp/comments/dz1sgk/find_the_number_of_structured_bindings_for_any/) to decompose a struct into its members.

**Note:** This library is not portable, and it only works with clang++ in C++ >=20.

## Example

```cpp
struct A{
    int a;
    int b;
};

A x{1, 2};
int n = decompose::decompose(x, [](auto&&... x){
    // x == {1, 2}
    return sizeof...(x);
});

assert(n == 2);
```

You can override the behavior of `decompose` either by specializing both `std::tuple_size` and `std::tuple_element` or by specializing `decompose::decompose_traits`.