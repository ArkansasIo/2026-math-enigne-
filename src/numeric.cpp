// ---------------------------------------------------------------------------
// MathEngine :: numeric.cpp
//
// Implementation of the numeric-layer vocabulary and the exact rational
// construction primitive.
// ---------------------------------------------------------------------------

#include <mathengine/numeric.hpp>

#include <numeric>   // std::gcd
#include <stdexcept> // std::invalid_argument
#include <string>

namespace mathengine {

const char* to_string(NumericKind kind) {
    switch (kind) {
        case NumericKind::Integer:  return "integer";
        case NumericKind::Rational: return "rational";
        case NumericKind::Real:     return "real";
        case NumericKind::Complex:  return "complex";
        case NumericKind::Interval: return "interval";
    }
    return "unknown";
}

double Rational::to_double() const noexcept {
    return static_cast<double>(num) / static_cast<double>(den);
}

std::string Rational::to_string() const {
    if (den == 1) {
        return std::to_string(num);
    }
    return std::to_string(num) + '/' + std::to_string(den);
}

Rational make_rational(long long num, long long den) {
    if (den == 0) {
        throw std::invalid_argument("mathengine::make_rational: zero denominator");
    }
    if (den < 0) {
        num = -num;
        den = -den;
    }
    const long long g = std::gcd(num < 0 ? -num : num, den);
    if (g > 1) {
        num /= g;
        den /= g;
    }
    return Rational{num, den};
}

} // namespace mathengine
