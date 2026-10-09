# MathEngine C++26

An extensible symbolic/numerical mathematics engine scaffold. It includes an initial working linear-integral API, a numeric type overview, buildable examples and tests, knowledge records, and an implementation roadmap.

## Build
Requirements: a compiler with C++26 support, CMake 3.25+, and a build tool such as Ninja or Make.

```bash
cmake -S . -B build -DMATHENGINE_BUILD_TESTS=ON -DMATHENGINE_BUILD_EXAMPLES=ON
cmake --build build
ctest --test-dir build --output-on-failure
./build/mathengine_cli
```

The C++26 toolchain support varies by compiler version. If your compiler does not yet support `-std=c++26`, use a current compiler preview or change the standard to C++23 temporarily.

## Current working example
`integrate_linear(3, 1)` represents the antiderivative of `3x + 1`:
`(3/2)x² + x + C`.

`definite_integral_linear(3, 1, 0, 5)` returns `42.5`.

## Important scope note
This is a starter implementation, not a complete Wolfram|Alpha replacement. Several modules are architectural interfaces or roadmap items, clearly documented as such. It does not use Wolfram's proprietary implementation.
