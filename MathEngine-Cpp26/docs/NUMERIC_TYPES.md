# Numeric Types and Libraries

## Built-in C++ types
- `bool`: truth values; not intended as a general arithmetic scalar.
- `char`, `signed char`, `unsigned char`: small integer types.
- `short`, `int`, `long`, `long long` and unsigned counterparts: integer families. Widths are implementation-dependent except minimum guarantees.
- `float`: typically single precision.
- `double`: typically double precision.
- `long double`: implementation-dependent extended precision.
- `std::intN_t` / `std::uintN_t`: exact-width integers when the implementation provides them.
- `std::size_t`: sizes and indexing, not a general signed integer.
- `std::complex<T>`: complex arithmetic for floating-point scalar types.
- `std::chrono::duration`: time quantities, not mathematical scalar replacement.

## Exact and extended precision
- Rational numbers: numerator/denominator with normalization and zero-denominator checks.
- Arbitrary-precision integers: consider Boost.Multiprecision `cpp_int`.
- Arbitrary-precision decimal/binary floating point: consider Boost.Multiprecision types.
- Symbolic expressions: use AST nodes rather than floating-point values when exact algebra matters.

## Candidate libraries
- **Boost.Multiprecision**: big integers and high-precision numeric types.
- **Eigen**: vectors, matrices, decompositions.
- **GMP/MPFR**: arbitrary-precision integers/rationals/floats, subject to platform and licensing review.
- **Catch2 or GoogleTest**: unit testing.
- **fmt**: formatting.
- **CLI11**: command-line parsing.
- **SymEngine**: optional symbolic-algebra integration; assess licensing/API fit before adopting.

These are optional dependencies, not bundled in this starter. Check each library's current license, compiler support and installation instructions before distributing.
