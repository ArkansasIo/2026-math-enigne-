#pragma once
#include <string>
namespace mathengine::knowledge {
struct EquationRecord { std::string id; std::string name; std::string equation; };
[[nodiscard]] EquationRecord linear_integral_equation();
}
