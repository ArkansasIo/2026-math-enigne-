# MathEngine Implementation Roadmap

This document is deliberately honest about what exists and what does not. The
repository is a **scaffold**: a small, real, tested core — the linear-integral
API — surrounded by clearly-labelled interfaces and roadmap items.

## Status legend

| Mark | Meaning |
| ---- | ------- |
| ✅   | Implemented, built, and covered by tests |
| 🟡   | Partially implemented (type or vocabulary exists, behaviour limited) |
| ⬜   | Roadmap item — architectural interface only, not yet functional |

## Modules

### Integral calculus
| Item | Status | Notes |
| ---- | ------ | ----- |
| `integrate_linear(a, b)` | ✅ | Exact symbolic `(a/2)x² + b x + C` |
| `definite_integral_linear(a, b, lo, hi)` | ✅ | Exact rational arithmetic, `double` at the boundary |
| Polynomial antiderivatives of arbitrary degree | ⬜ | Needs a polynomial representation |
| Symbolic integration (by parts, substitution) | ⬜ | Needs an expression tree |
| Numeric quadrature (Simpson, Gauss–Kronrod) | ⬜ | Needs function-object interface |

### Numeric layer
| Item | Status | Notes |
| ---- | ------ | ----- |
| `NumericKind` enumeration | ✅ | Vocabulary for downstream modules |
| `Rational` + `make_rational` | ✅ | Exact reduced fractions, gcd-normalised |
| Arbitrary-precision integers | ⬜ | Planned on top of a bignum backend |
| Complex numbers | ⬜ | Planned |
| Interval arithmetic | ⬜ | Planned |
| Vector / matrix numeric types | ⬜ | Planned |

### Front-end
| Item | Status | Notes |
| ---- | ------ | ----- |
| CLI REPL for the working API | ✅ | `integrate`, `definite`, `demo`, `help`, `quit` |
| Expression parser for free-form input | ⬜ | Needed before general symbolic work |
| LaTeX / pretty printer | ⬜ | `SymbolicResult::to_string` is a first step |

## Suggested next steps

1. Introduce an expression tree (`Expr`) so integration is not hard-wired to
   linear polynomials. Almost every ⬜ above depends on this.
2. Replace the `Rational` struct with a first-class number type that can hold
   integer, rational, real, and complex values in one `NumericKind`-tagged
   variant.
3. Add polynomial arithmetic (add, multiply, differentiate, integrate) as the
   first real *symbolic* capability.
4. Wire a recursive-descent parser to the CLI so `integrate` accepts `3x + 1`
   instead of two integers.

## Non-goals / honesty clause

- This project does **not** aim to be a complete Wolfram|Alpha replacement.
- It does **not** use, embed, or reimplement Wolfram's proprietary code.
- Modules marked ⬜ are interfaces and intentions, not working features.
