#include <cassert>
#include <decompose/decompose.hpp>
#include <cstdio>

struct A{
    int a;
    int b;
};

int main(){
    A x{1, 2};
    decompose::decompose(x, [](auto... y){
        static_assert(sizeof...(y) == 2);
        std::printf("%d %d\n", y...);
        int z[2] = {y...};
        assert(z[0] == 1);
        assert(z[1] == 2);
    });
}