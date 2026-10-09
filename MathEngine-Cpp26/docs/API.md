# API Overview

Current:
- `mathengine::calculus::integrate_linear(a, b)` returns a formatted antiderivative for `a*x + b`.
- `mathengine::calculus::definite_integral_linear(a, b, lower, upper)` evaluates the definite integral numerically.
- `mathengine::numerics::NumericInfo` records type traits for common built-in floating-point types.

Planned API:
- `derivative(expression, variable)`
- `integrate(expression, variable)`
- `definite_integral(expression, variable, lower, upper)`
- `limit(expression, variable, point)`
- `simplify`, `expand`, `factor`, `solve`
- `find_theorem`, `find_equation`, `find_term`
