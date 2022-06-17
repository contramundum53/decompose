# Decompose

A simple header-only library implementing [htjf's trick](https://www.reddit.com/r/cpp/comments/dz1sgk/find_the_number_of_structured_bindings_for_any/) to decompose a struct into its members.

**Note:** This library is not portable, and it only works with clang++ in C++ >=20.

## Requirements
* C++ >= 20
* clang++

## Preparation
This is a header-only library. Just add `include` directory into your include path.
Alternatively, if you use `cmake`, you can `add_subdirectory` this library and use `decompose` target.
```cmake
add_subdirectory(path/to/this/directory)
target_link_library(your_target decompose)
```

## Example

```cpp
#include <decompose/decompose.hpp>
#include <cassert>

struct A{
    int a;
    int b;
};

int main(){
    A x{1, 2};
    int n = decompose::decompose(x, [](auto&&... x){
        // x == {1, 2}
        return sizeof...(x);
    });

    assert(n == 2);
}
```

You can override the behavior of `decompose` either by specializing both `std::tuple_size` and `std::tuple_element` or by specializing `decompose::decompose_traits`.