#pragma once
#include <type_traits>

#include <utility>
#include <tuple>
#include <concepts>

#include "detail/util.hpp"
#include "detail/decompose_with_structured_binding.hpp"

namespace decompose{

template<class T>
struct decompose_traits;

template<class T>
concept decomposable = detail::is_complete<decompose_traits<T>> || detail::decomposable_with_structured_binding<T>;

template<class T, class F>
constexpr decltype(auto) decompose(T&& t, F&& f){
    using traits = decompose_traits<std::decay_t<T>>;
    if constexpr (detail::is_complete<traits>){
        return traits::decompose(std::forward<T>(t), std::forward<F>(f));
    } else{
        return detail::decompose_with_structured_binding(std::forward<T>(t), std::forward<F>(f));
    }
}

}