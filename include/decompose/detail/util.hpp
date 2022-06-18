#pragma once
#include <type_traits>
#include <concepts>
#include <utility>
namespace decompose::detail{

template <class... Ts>
struct overload_t : Ts... {
    constexpr overload_t(const Ts&... ts) : Ts(std::move(ts))... {}
    using Ts::operator()...;
};
struct any{
    template<class T>
    constexpr any(T&& t) {}
};
template<class T>
concept is_complete = (
    decltype(overload_t{[]<class U, std::size_t sz = sizeof(U)>(U*, int)->std::true_type{return {};},
                                  []<class U>(U*, float) -> std::false_type {return {};}}((T*)nullptr, 0))::value);
}