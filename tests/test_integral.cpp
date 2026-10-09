// ---------------------------------------------------------------------------
// MathEngine :: tests
//
// A dependency-free test executable. It exits non-zero on the first failure so
// CTest reports a clean pass/fail without needing an external framework.
// ---------------------------------------------------------------------------

#include <mathengine/mathengine.hpp>

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>

namespace
{

    int failures = 0;
    int checks = 0;

    void report(bool ok, const std::string &what)
    {
        ++checks;
        if (ok)
        {
            std::cout << "  [ ok ] " << what << '\n';
        }
        else
        {
            ++failures;
            std::cout << "  [FAIL] " << what << '\n';
        }
    }

    bool nearly_equal(double a, double b, double eps = 1e-12)
    {
        return std::fabs(a - b) <= eps;
    }

    void test_symbolic_known_example()
    {
        const auto r = mathengine::integrate_linear(3, 1);
        report(r.quadratic_num == 3 && r.quadratic_den == 2,
               "integrate_linear(3,1) has quadratic coefficient 3/2");
        report(r.linear_num == 1 && r.linear_den == 1,
               "integrate_linear(3,1) has linear coefficient 1");
        report(r.to_string() == "(3/2)x\u00B2 + x + C",
               "integrate_linear(3,1) renders exactly '(3/2)x\u00B2 + x + C'");
    }

    void test_symbolic_reduction()
    {
        // a = 4 -> (4/2)x² + ... reduces to 2x².
        const auto r = mathengine::integrate_linear(4, 0);
        report(r.quadratic_num == 2 && r.quadratic_den == 1,
               "integrate_linear(4,0) reduces 4/2 to 2");

        // Negative linear coefficient renders with a minus sign.
        const auto neg = mathengine::integrate_linear(2, -3);
        report(neg.linear_num == -3 && neg.linear_den == 1,
               "integrate_linear(2,-3) keeps the sign of b");
    }

    void test_definite_known_example()
    {
        const double v = mathengine::definite_integral_linear(3, 1, 0, 5);
        report(nearly_equal(v, 42.5),
               "definite_integral_linear(3,1,0,5) == 42.5");
    }

    void test_definite_consistency_with_symbolic()
    {
        // ∫_0^2 (3x + 1) dx = (3/2)x² + x |_0^2 = 6 + 2 = 8
        const double v = mathengine::definite_integral_linear(3, 1, 0, 2);
        report(nearly_equal(v, 8.0),
               "definite_integral_linear(3,1,0,2) == 8");

        // Reversed limits invert the sign: ∫_5^0 = -42.5
        const double reversed = mathengine::definite_integral_linear(3, 1, 5, 0);
        report(nearly_equal(reversed, -42.5),
               "definite_integral_linear(3,1,5,0) == -42.5");
    }

    void test_rational_layer()
    {
        const auto r = mathengine::make_rational(4, -6);
        report(r.num == -2 && r.den == 3,
               "make_rational(4,-6) normalises to -2/3");
        report(r.to_string() == "-2/3", "Rational::to_string renders -2/3");

        const auto whole = mathengine::make_rational(10, 2);
        report(whole.num == 5 && whole.den == 1,
               "make_rational(10,2) normalises to 5");

        bool threw = false;
        try
        {
            (void)mathengine::make_rational(1, 0);
        }
        catch (const std::invalid_argument &)
        {
            threw = true;
        }
        report(threw, "make_rational(x,0) throws std::invalid_argument");
    }

    void test_numeric_kind_names()
    {
        report(std::string(mathengine::to_string(mathengine::NumericKind::Rational)) ==
                   "rational",
               "to_string(NumericKind::Rational) == \"rational\"");
    }

} // namespace

int main()
{
    std::cout << "MathEngine test suite\n";

    test_symbolic_known_example();
    test_symbolic_reduction();
    test_definite_known_example();
    test_definite_consistency_with_symbolic();
    test_rational_layer();
    test_numeric_kind_names();

    std::cout << "\n"
              << (checks - failures) << '/' << checks
              << " checks passed.\n";

    if (failures != 0)
    {
        std::cout << failures << " check(s) FAILED.\n";
        return EXIT_FAILURE;
    }
    std::cout << "All tests passed.\n";
    return EXIT_SUCCESS;
}
