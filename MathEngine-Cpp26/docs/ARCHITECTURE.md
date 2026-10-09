# Architecture

Input -> Lexer/Parser -> Expression AST -> Algebra/Calculus/Numerical algorithms -> Verification -> Result.

- **Core**: common types, errors, result metadata.
- **Numbers**: numeric type traits and adapters.
- **Expressions/AST**: symbolic expression representation.
- **Algebra/Calculus**: symbolic transformations.
- **Numerics**: numeric evaluation and algorithms.
- **Knowledge**: structured records separate from executable rules.
- **Verification**: domain checks and identity checks.

Prefer exact symbolic results where practical; use numerical approximations explicitly and preserve domain assumptions.
