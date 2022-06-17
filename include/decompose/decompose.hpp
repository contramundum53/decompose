#pragma once
#include <type_traits>

#include <utility>
#include <tuple>
#include <concepts>

#include "decompose_with_structured_binding.hpp"

namespace decompose{

template<class T>
struct decompose_traits{
    template<class U, class F> requires std::same_as<std::decay_t<U>, T>
    static constexpr decltype(auto) decompose(U&& u, F&& f){
        return decompose_with_structured_binding(std::forward<U>(u), std::forward<F>(f));
    }
};

template<class T, class F>
constexpr decltype(auto) decompose(T&& t, F&& f){
    return decompose_traits<std::decay_t<T>>::decompose(std::forward<T>(t), std::forward<F>(f));
}

}