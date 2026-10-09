#ifndef MATHENGINE_INTEGRAL_HPP
#define MATHENGINE_INTEGRAL_HPP

// ---------------------------------------------------------------------------
// MathEngine :: integral
//
// Symbolic integer-antiderivative helpers for polynomials, plus a numeric
// definite-integral entry point. This is the initial *working* API of the
// engine: two signatures, fully implemented and tested.
//
//   integrate_linear(a, b)  ->  symbolic result of  ∫(a*x + b) dx
//   definite_integral_linear(a, b, lo, hi) -> numeric ∫_lo^hi (a*x + b) dx
//
// The symbolic result is returned as a `SymbolicResult` value object rather
// than a string so callers can inspect the coefficients programmatically and
// only format for display when they choose to.
// ---------------------------------------------------------------------------

#include <string>

namespace mathengine
{

    /// A symbolic antiderivative of the form  (p/q) * x^2 + (r/s) * x + C.
    ///
    /// Coefficients are kept as exact integer fractions to avoid the rounding
    /// artefacts that a naive `double` representation would introduce for inputs
    /// such as `a = 1, b = 1` (where the leading term is exactly 1/2).
    struct SymbolicResult
    {
        /// Numerator of the x^2 coefficient.
        long long quadratic_num{0};
        /// Denominator of the x^2 coefficient (never zero).
        long long quadratic_den{1};
        /// Numerator of the x coefficient.
        long long linear_num{0};
        /// Denominator of the x coefficient (never zero).
        long long linear_den{1};
        /// Whether the implicit `+ C` constant is present.
        bool has_constant{true};

        /// Human-readable form using Unicode superscripts, e.g. "(3/2)x² + x + C".
        [[nodiscard]] std::string to_string() const;
    };

    /// Returns the symbolic antiderivative of the linear expression `a*x + b`:
    ///
    ///     ∫ (a*x + b) dx = (a/2) x² + b x + C
    ///
    /// The result is exact. For `a = 3, b = 1` this yields `(3/2)x² + x + C`.
    [[nodiscard]] SymbolicResult integrate_linear(long long a, long long b);

    /// Returns the numeric value of the definite integral of `a*x + b` on `[lo, hi]`:
    ///
    ///     ∫_lo^hi (a*x + b) dx = (a/2)(hi² - lo²) + b(hi - lo)
    ///
    /// Uses exact rational arithmetic internally and only converts to `double` at
    /// the very end, so `definite_integral_linear(3, 1, 0, 5)` returns exactly
    /// `42.5`.
    [[nodiscard]] double definite_integral_linear(long long a,
                                                  long long b,
                                                  long long lo,
                                                  long long hi);

} // namespace mathengine

#endif // MATHENGINE_INTEGRAL_HPP
