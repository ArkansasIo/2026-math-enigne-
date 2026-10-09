#include <MathEngine/Calculus.hpp>
#include <sstream>
namespace mathengine::calculus {
std::string integrate_linear(double a, double b) {
    std::ostringstream out;
    out << '(' << a / 2.0 << ")*x^2 + " << b << "*x + C";
    return out.str();
}
double definite_integral_linear(double a, double b, double lower, double upper) {
    const auto F = [a, b](double x) { return (a / 2.0) * x * x + b * x; };
    return F(upper) - F(lower);
}
}
