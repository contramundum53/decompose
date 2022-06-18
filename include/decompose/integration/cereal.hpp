#pragma once

#if !__has_include(<cereal/cereal.hpp>)
#error "integration/cereal.hpp requires cereal/cereal.hpp"
#endif
#include <cereal/cereal.hpp>

#include <decompose/decompose.hpp>

namespace cereal{
    template <class Archive, class T> requires (traits::has_member_serialize<T, Archive>::value == 0
            && traits::has_member_load<T, Archive>::value == 0
            && traits::has_member_save<T, Archive>::value == 0
            && traits::has_non_member_load<T, Archive>::value == 0
            && traits::has_non_member_save<T, Archive>::value == 0) && decompose::decomposable<T>
    void serialize(Archive& ar, T& obj){
        decompose::decompose(obj, [&ar](auto&&... args){
            ar(std::forward<decltype(args)>(args)...);
        });        
    }
}
