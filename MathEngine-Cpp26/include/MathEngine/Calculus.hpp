#pragma once
#include <string>
namespace mathengine::calculus {
[[nodiscard]] std::string integrate_linear(double a, double b);
[[nodiscard]] double definite_integral_linear(double a, double b, double lower, double upper);
}
