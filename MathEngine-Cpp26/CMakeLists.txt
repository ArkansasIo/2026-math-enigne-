cmake_minimum_required(VERSION 3.25)
project(MathEngine VERSION 0.2.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(MATHENGINE_BUILD_TESTS "Build tests" ON)
option(MATHENGINE_BUILD_EXAMPLES "Build examples" ON)

add_library(MathEngine
    src/Calculus.cpp
    src/Algebra.cpp
    src/Numerics.cpp
    src/Knowledge.cpp)
target_include_directories(MathEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
if(MSVC)
  target_compile_options(MathEngine PRIVATE /W4 /permissive-)
else()
  target_compile_options(MathEngine PRIVATE -Wall -Wextra -Wpedantic)
endif()

if(MATHENGINE_BUILD_EXAMPLES)
  add_executable(mathengine_cli src/main.cpp)
  target_link_libraries(mathengine_cli PRIVATE MathEngine)
endif()
if(MATHENGINE_BUILD_TESTS)
  enable_testing()
  add_executable(MathEngineTests tests/test_mathengine.cpp)
  target_link_libraries(MathEngineTests PRIVATE MathEngine)
  add_test(NAME MathEngineTests COMMAND MathEngineTests)
endif()
