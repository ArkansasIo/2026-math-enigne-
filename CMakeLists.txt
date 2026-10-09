cmake_minimum_required(VERSION 3.25)

project(MathEngine
    VERSION 0.1.0
    DESCRIPTION "An extensible symbolic/numerical mathematics engine scaffold"
    LANGUAGES CXX)

# ---------------------------------------------------------------------------
# Options
# ---------------------------------------------------------------------------
option(MATHENGINE_BUILD_TESTS    "Build the MathEngine test suite"  OFF)
option(MATHENGINE_BUILD_EXAMPLES "Build the MathEngine examples"    OFF)
option(MATHENGINE_BUILD_CLI      "Build the MathEngine CLI"         ON)

# ---------------------------------------------------------------------------
# Language standard
# ---------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Export compile commands for tooling (clangd, etc.)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ---------------------------------------------------------------------------
# Library
# ---------------------------------------------------------------------------
add_library(mathengine
    src/integral.cpp
    src/numeric.cpp)

target_include_directories(mathengine
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)

target_compile_features(mathengine PUBLIC cxx_std_26)

if(MSVC)
    target_compile_options(mathengine PRIVATE /W4 /permissive-)
else()
    target_compile_options(mathengine PRIVATE -Wall -Wextra -Wpedantic)
endif()


# ---------------------------------------------------------------------------
# CLI executable
# ---------------------------------------------------------------------------
if(MATHENGINE_BUILD_CLI)
    add_executable(mathengine_cli src/cli/main.cpp)
    target_link_libraries(mathengine_cli PRIVATE mathengine)
endif()

# ---------------------------------------------------------------------------
# Examples
# ---------------------------------------------------------------------------
if(MATHENGINE_BUILD_EXAMPLES)
    add_executable(mathengine_example_basic examples/basic.cpp)
    target_link_libraries(mathengine_example_basic PRIVATE mathengine)
endif()

# ---------------------------------------------------------------------------
# Tests
# ---------------------------------------------------------------------------
if(MATHENGINE_BUILD_TESTS)
    enable_testing()

    add_executable(mathengine_tests tests/test_integral.cpp)
    target_link_libraries(mathengine_tests PRIVATE mathengine)

    add_test(NAME mathengine_tests COMMAND mathengine_tests)
endif()
