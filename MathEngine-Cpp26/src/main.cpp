#include <MathEngine/Calculus.hpp>
#include <iostream>
int main() {
    using namespace mathengine::calculus;
    std::cout << "MathEngine C++26 starter\n";
    std::cout << "Integral of 3x + 1: " << integrate_linear(3.0, 1.0) << '\n';
    std::cout << "Integral from 0 to 5: "
              << definite_integral_linear(3.0, 1.0, 0.0, 5.0) << '\n';
}
