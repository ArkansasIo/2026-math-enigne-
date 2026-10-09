#include <MathEngine/Calculus.hpp>
#include <MathEngine/Numerics.hpp>
#include <cassert>
#include <cmath>
#include <iostream>
int main() {
    using mathengine::calculus::definite_integral_linear;
    assert(std::abs(definite_integral_linear(3.0, 1.0, 0.0, 5.0) - 42.5) < 1e-12);
    static_assert(mathengine::numerics::NumericInfo<float>::is_floating_point);
    static_assert(mathengine::numerics::NumericInfo<double>::is_floating_point);
    static_assert(mathengine::numerics::NumericInfo<long double>::is_floating_point);
    static_assert(mathengine::numerics::NumericInfo<int>::is_integer);
    std::cout << "All MathEngine tests passed.\\n";
}
