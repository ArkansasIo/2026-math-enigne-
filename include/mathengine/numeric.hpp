#ifndef MATHENGINE_NUMERIC_HPP
#define MATHENGINE_NUMERIC_HPP

// ---------------------------------------------------------------------------
// MathEngine :: numeric
//
// Overview of the numeric types the engine is designed around, and the shared
// construction primitive used by the working API.
//
// Only `make_rational` is currently implemented and exercised; the type
// enumeration below documents the intended numeric layer so that downstream
// modules (solvers, series, root-finding) can agree on a vocabulary.
// ---------------------------------------------------------------------------

#include <string>

namespace mathengine
{

    /// The numeric domains the engine aims to support, from most exact to most
    /// approximate. Rendering and arithmetic code should dispatch on this enum
    /// rather than on `typeid`/`std::variant` indices.
    enum class NumericKind
    {
        Integer,  ///< Exact arbitrary-precision integer            (roadmap)
        Rational, ///< Exact fraction p/q                           (partially used)
        Real,     ///< IEEE-754 double                               (in use)
        Complex,  ///< Complex numbers                              (roadmap)
        Interval, ///< Bounded interval arithmetic                  (roadmap)
    };

    /// Returns a stable, lower-case name for a `NumericKind`.
    [[nodiscard]] const char *to_string(NumericKind kind);

    /// A minimal exact rational value: `num / den`.
    ///
    /// The invariant maintained by `make_rational` is that `den > 0` and that the
    /// fraction is reduced to lowest terms (so `make_rational(4, -6)` becomes
    /// `-2/3`). A zero denominator is a programming error and throws
    /// `std::invalid_argument`.
    struct Rational
    {
        long long num{0};
        long long den{1};

        /// Approximate floating-point value of the fraction.
        [[nodiscard]] double to_double() const noexcept;

        /// Human-readable form, e.g. "-2/3" or "5" when the denominator is one.
        [[nodiscard]] std::string to_string() const;
    };

    /// Constructs a `Rational` in canonical form (reduced, positive denominator).
    ///
    /// @throws std::invalid_argument if `den == 0`.
    [[nodiscard]] Rational make_rational(long long num, long long den);

} // namespace mathengine

#endif // MATHENGINE_NUMERIC_HPP
