// ---------------------------------------------------------------------------
// MathEngine :: basic example
//
// The smallest possible program using the engine, kept in sync with the
// "Current working example" section of the README.
// ---------------------------------------------------------------------------

#include <mathengine/mathengine.hpp>

#include <iostream>

int main()
{
    // Symbolic antiderivative of 3x + 1  ->  (3/2)x² + x + C
    const auto antiderivative = mathengine::integrate_linear(3, 1);
    std::cout << "integrate_linear(3, 1)  = " << antiderivative.to_string()
              << '\n';

    // Numeric definite integral over [0, 5]  ->  42.5
    const double area = mathengine::definite_integral_linear(3, 1, 0, 5);
    std::cout << "definite_integral_linear(3, 1, 0, 5) = " << area << '\n';

    // The exact rational layer behind the symbolic result.
    const auto half = mathengine::make_rational(4, -6); // reduces to -2/3
    std::cout << "make_rational(4, -6)    = " << half.to_string()
              << "  (~" << half.to_double() << ")\n";

    return 0;
}
