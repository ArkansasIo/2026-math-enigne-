#include <MathEngine/Knowledge.hpp>
namespace mathengine::knowledge {
EquationRecord linear_integral_equation() {
    return {"calculus.linear.integral", "Antiderivative of ax+b",
            "Integral((a*x+b),x) = (a/2)*x^2 + b*x + C"};
}
}
