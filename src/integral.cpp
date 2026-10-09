// ---------------------------------------------------------------------------
// MathEngine :: integral.cpp
//
// Implementation of the working symbolic/numeric integral API.
//
// Everything here is computed with 64-bit integer arithmetic and only reduced
// to `double` at the outermost boundary, keeping the documented examples
// (`(3/2)x² + x + C`, `42.5`) exact rather than approximately correct.
// ---------------------------------------------------------------------------

#include <mathengine/integral.hpp>

#include <numeric>   // std::gcd
#include <stdexcept> // std::runtime_error (overflow guards)
#include <string>

namespace mathengine
{
    namespace
    {

        /// Reduces `num/den` to lowest terms with a strictly positive denominator.
        /// A zero denominator is treated as an internal invariant violation.
        void reduce(long long &num, long long &den)
        {
            if (den == 0)
            {
                throw std::runtime_error("mathengine::integral: zero denominator");
            }
            if (den < 0)
            {
                num = -num;
                den = -den;
            }
            const long long g = std::gcd(num < 0 ? -num : num, den);
            if (g > 1)
            {
                num /= g;
                den /= g;
            }
        }

        /// Appends `num/den` as a coefficient: a fraction is wrapped in
        /// parentheses so it binds correctly against a following `x`, and a
        /// denominator of one collapses to the bare integer. A numerator of zero
        /// reports `*is_zero` so the caller can skip the whole term.
        void append_coefficient(std::string &out, long long num, long long den,
                                bool &is_zero)
        {
            is_zero = (num == 0);
            if (is_zero)
            {
                return;
            }
            if (den != 1)
            {
                out += '(';
                out += std::to_string(num);
                out += '/';
                out += std::to_string(den);
                out += ')';
            }
            else
            {
                out += std::to_string(num);
            }
        }

        /// True when `num/den` is exactly the value 1 (e.g. 1/1 or 2/2).
        bool is_unit(long long num, long long den)
        {
            return num == den && num != 0;
        }

    } // namespace

    std::string SymbolicResult::to_string() const
    {
        std::string out;
        bool zero_term = false;

        // Quadratic term. A coefficient of exactly 1 is written as a bare `x²`
        // (i.e. `x²`, not `1x²`), matching the README's rendering conventions.
        if (!is_unit(quadratic_num, quadratic_den))
        {
            append_coefficient(out, quadratic_num, quadratic_den, zero_term);
        }
        if (quadratic_num != 0)
        {
            out += "x\u00B2"; // "x²"
        }

        // Linear term, with an explicit sign when appended after the quadratic one.
        bool linear_zero = false;
        std::string linear_text;
        const long long abs_linear_num = linear_num < 0 ? -linear_num : linear_num;
        if (!is_unit(abs_linear_num, linear_den)) {
            // Only print the magnitude of the coefficient; the sign is handled by
            // the separator, so `-1x` renders as `- x` rather than `- 1x`.
            append_coefficient(linear_text, abs_linear_num, linear_den, linear_zero);
        }
        if (linear_num != 0) {
            if (!out.empty()) {
                out += (linear_num < 0) ? " - " : " + ";
            } else if (linear_num < 0) {
                out += '-';
            }
            out += linear_text;
            out += 'x';
        }

        // Constant of integration.
        if (has_constant)
        {
            if (!out.empty())
            {
                out += " + ";
            }
            out += 'C';
        }

        if (out.empty())
        {
            out = "0";
        }
        return out;
    }

    SymbolicResult integrate_linear(long long a, long long b)
    {
        // ∫ (a*x + b) dx = (a/2) x² + b x + C
        SymbolicResult result;
        result.quadratic_num = a;
        result.quadratic_den = 2;
        reduce(result.quadratic_num, result.quadratic_den);

        result.linear_num = b;
        result.linear_den = 1;
        reduce(result.linear_num, result.linear_den);

        result.has_constant = true;
        return result;
    }

    double definite_integral_linear(long long a, long long b, long long lo,
                                    long long hi)
    {
        // ∫_lo^hi (a*x + b) dx = (a/2)(hi² - lo²) + b(hi - lo)
        // Combine over the common denominator 2 to stay in exact arithmetic.
        const long long squared_diff = hi * hi - lo * lo; // hi² - lo²
        const long long width = hi - lo;                  // hi - lo

        const long long numerator = a * squared_diff + 2 * b * width;
        const long long denominator = 2;

        long long num = numerator;
        long long den = denominator;
        reduce(num, den);

        return static_cast<double>(num) / static_cast<double>(den);
    }

} // namespace mathengine
