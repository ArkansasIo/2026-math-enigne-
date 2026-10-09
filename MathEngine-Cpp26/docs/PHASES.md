# Implementation Phases

0. **Foundation** — build system, public API, tests, style, CI.
1. **Numeric types** — fixed-width integers, floats, doubles, long double, complex, rational and arbitrary precision adapters.
2. **Expression/AST** — immutable nodes, symbols, constants, operators, function calls, visitors.
3. **Parser/printer** — lexer, grammar, expression parsing, pretty printing.
4. **Algebra** — simplify, expand, factor, collect, substitutions, polynomial arithmetic, equation solving.
5. **Differential calculus** — symbolic derivatives, chain/product/quotient rules, gradients and Jacobians.
6. **Integral calculus** — antiderivatives, definite and improper integrals, substitutions, integration by parts, numerical quadrature.
7. **Limits and series** — one-sided limits, limits at infinity, Taylor series, convergence tests.
8. **Linear algebra** — vectors, matrices, determinants, eigenvalues, linear systems and decompositions.
9. **Differential equations** — ODE/PDE representations, initial and boundary conditions, numerical solvers.
10. **Probability/statistics** — distributions, expectation, variance, regression and inference.
11. **Numerical methods** — root finding, optimization, interpolation, adaptive integration and error estimates.
12. **Mathematical knowledge base** — axioms, definitions, theorems, lemmas, corollaries, identities, equations, terms, proofs and references.
13. **Verification** — domain checking, assumptions, identity checking, units/dimensions, provenance.
14. **Advanced fields** — number theory, abstract algebra, topology, analysis, graph theory, combinatorics, mathematical physics.
15. **Applications** — CLI/REPL, API server, notebooks, visualization and educational mode.

Each phase should add tests and document preconditions, domains, limitations, and algorithmic complexity.
