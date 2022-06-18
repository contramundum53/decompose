#include <cassert>
#include <decompose/decompose.hpp>
#include <cstdio>


struct A{ // decomposable
    int a;
    int b;
};

struct E {}; // Empty classes are decomposable
struct B : E{ // decomposable because all fields are in this class
    A a;
};
struct D: B{ // Both its base class and its member has fields, so it is not decomposable.
    int b; 
};

struct F: B{ // decompose::decompose_traits<F> is specialized, so this is decomposable.
    int b;
};
namespace decompose{
    template<>
    struct decompose_traits<F>{
        template<class T, class G>
        static void decompose(T&& t, G&& g){
            std::forward<G>(g)(std::forward<T>(t).a.a, std::forward<T>(t).a.b, std::forward<T>(t).b);
        }
    };
}

int main(){

    A x{1, 2};
    static_assert(decompose::decomposable<A>);
    decompose::decompose(x, [](auto... y){
        static_assert(sizeof...(y) == 2);
        std::printf("%d %d\n", y...);
        int z[2] = {y...};
        assert(z[0] == 1);
        assert(z[1] == 2);
    });

    static_assert(decompose::decomposable<E>);
    static_assert(decompose::decomposable<B>);
    static_assert(!decompose::decomposable<D>);

    static_assert(decompose::decomposable<F>);
    F x2 = {B{{}, A{1, 2}}, 3};
    decompose::decompose(x2, [](auto... y){
        static_assert(sizeof...(y) == 3);
        std::printf("%d %d %d\n", y...);
        int z[3] = {y...};
        assert(z[0] == 1);
        assert(z[1] == 2);
        assert(z[2] == 3);
    });


}