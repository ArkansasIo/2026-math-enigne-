#pragma once
#include <complex>
#include <limits>
#include <type_traits>
namespace mathengine::numerics {
template<class T>
struct NumericInfo {
    static_assert(std::is_arithmetic_v<T>, "NumericInfo requires a built-in arithmetic type");
    static constexpr bool is_integer = std::is_integral_v<T>;
    static constexpr bool is_floating_point = std::is_floating_point_v<T>;
    static constexpr int digits = std::numeric_limits<T>::digits;
    static constexpr int max_exponent = std::numeric_limits<T>::max_exponent;
};
template<class T>
using Complex = std::complex<T>;
}
