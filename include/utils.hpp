#pragma once
#include <cmath>
#include <type_traits>


template <typename T>
T mod(T const & a, T const & b) {
    static_assert(std::is_floating_point<T>::value, "Floating point type required!");
    return a - b*std::floor(a/b);

}