#include <decompose/integration/cereal.hpp>

#include <cereal/archives/binary.hpp>
#include <sstream>
struct A{
    int a, b;
};
int main(){
    std::stringstream ss;
    {
        cereal::BinaryOutputArchive ar(ss);
        A x{1, 2};
        ar(x);
    }
    {
        cereal::BinaryInputArchive ar(ss);
        A x;
        ar(x);
        assert(x.a == 1);
        assert(x.b == 2);
    }
    return 0;

}