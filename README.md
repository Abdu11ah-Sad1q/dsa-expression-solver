# Expression Conversion and Evaluation System

A robust command-line C++ application that reads infix arithmetic expressions, converts them into postfix notation (Reverse Polish Notation), manages dynamic variable value acquisition using 64-bit precision data types, and evaluates the mathematical results using stacks.

## Project Features
- **64-Bit Numeric Precision:** Utilizes `long long` data types for evaluation and storage to handle larger calculation capacities without integer overflow risks.
- [cite_start]**Tokenization Engine:** Gracefully parses multi-digit integers and multi-character variable names that fully comply with standard C++ identifier rules[cite: 11, 12, 16].
- [cite_start]**Grouping Symbol Validation:** Robustly processes matching rules for multiple standard grouping symbols, including `()`, `[]`, and `{}`[cite: 10, 25].
- [cite_start]**Strict Stream Isolation:** Prompts for variable values and all diagnostic error descriptions are explicitly routed to `stderr`[cite: 36, 41, 43, 44]. [cite_start]Only the final processed postfix expression and its evaluated outcome are written to `stdout`[cite: 37].
- [cite_start]**Exit Code Integration:** Terminates cleanly with predictable exit codes (`0`, `1`, `2`, or `3`) depending on the exact execution or error scenario encountered[cite: 39, 40, 41, 43, 44].

## Compiling the Code

[cite_start]This project is written using standard C++11 library components and does not require any external dependencies. You can compile it using any standard C++ compiler like `g++`:

```bash
g++ -std=c++11 main.cpp -o expression_solver
