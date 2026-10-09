# MathEngine Knowledge Records

Design decisions and reference notes for the engine. Each record states the
context, the decision, and the consequences, so future contributors understand
*why* the code looks the way it does.

---

## KR-0001 — Exact rationals instead of `double` in the integral core

**Context.** The README advertises the results `(3/2)x² + x + C` and `42.5`.
A naive `double` implementation of `∫(a x + b)` would compute `a / 2.0` and
could surface values like `1.4999999999999998`.

**Decision.** The symbolic result stores coefficients as `long long` numerator
/ denominator pairs (`SymbolicResult`). The definite integral combines terms
over the common denominator `2` and reduces with `std::gcd` before converting
to `double` exactly once.

**Consequences.**
- Advertised examples are exact, not merely close.
- Coefficients are inspectable programmatically, not just printable.
- Inputs are limited to `long long`; overflow is possible for very large `a`,
  `b`, `lo`, `hi` (see KR-0003).

---

## KR-0002 — `NumericKind` as a dispatch vocabulary

**Context.** Future modules (solvers, series, root-finding) must agree on what
kinds of numbers exist.

**Decision.** Introduce the `NumericKind` enum now, even though only `Rational`
and `Real` are exercised, so that rendering and arithmetic code can dispatch on
one stable enumeration instead of `typeid` or variant indices.

**Consequences.**
- Adding a numeric domain is an enum extension plus a `to_string` case.
- The enum documents intent; entries without an implementation are roadmap
  items and are labelled as such in `docs/ROADMAP.md`.

---

## KR-0003 — Known limitations & TODO

These are recorded deliberately rather than hidden:

1. **Overflow.** `definite_integral_linear` squares its bounds
   (`hi * hi - lo * lo`) in `long long`. Bounds beyond roughly `±3×10⁹` can
   overflow. A future bignum integer layer (ROADMAP, Numeric layer) fixes this.
2. **Degree-1 only.** Both functions assume a linear integrand. General
   polynomials and transcendental integrands require an expression tree.
3. **No parser.** The CLI reads integers positionally; it cannot parse the
   string `3x + 1`. This is intentional for the scaffold stage.
4. **No external test framework.** Tests are hand-rolled in
   `tests/test_integral.cpp` to keep the build dependency-free. If the suite
   grows past a few hundred lines, adopt Catch2 or GoogleTest.

---

## KR-0004 — Non-affiliation

The engine is an independent educational scaffold. It does not use Wolfram's
proprietary implementation and is not a Wolfram|Alpha replacement. Any
comparison to such products is about *scope*, not compatibility.

---

## Versioning

`MATHENGINE_VERSION_*` macros in `include/mathengine/mathengine.hpp` are the
single source of truth for the version string reported by `--version`. Keep
them in sync with `project(... VERSION ...)` in the root `CMakeLists.txt`.
