# Expression Conversion and Evaluation System

A robust command-line C++ application that reads infix arithmetic expressions, converts them into postfix notation (Reverse Polish Notation), manages dynamic variable value acquisition using 64-bit precision data types, and evaluates the mathematical results using stacks.

---

## Project Features

* **64-Bit Numeric Precision:** Utilizes `long long` data types for evaluation and storage to handle larger calculation capacities without integer overflow risks.
* **Tokenization Engine:** Gracefully parses multi-digit integers and multi-character variable names that fully comply with standard C++ identifier rules.
* **Grouping Symbol Validation:** Robustly processes matching rules for multiple standard grouping symbols, including `()`, `[]`, and `{}`.
* **Strict Stream Isolation:** Prompts for variable values and all diagnostic error descriptions are explicitly routed to `stderr`. Only the final processed postfix expression and its evaluated outcome are written to `stdout`.
* **Exit Code Integration:** Terminates cleanly with predictable exit codes (`0`, `1`, `2`, or `3`) depending on the exact execution or error scenario encountered.

---

## Technical Specifications

### Exit Codes Matrix
If the program terminates unexpectedly, it will return one of the following exit codes based on the issue encountered:

| Exit Code | Classification | Description |
| :---: | :--- | :--- |
| **0** | Success | Everything ran cleanly from parsing to final evaluation. |
| **1** | Syntax Error | Mismatched brackets, unclosed grouping symbols, illegal characters, or insufficient operands. |
| **2** | Runtime Error | Division by zero or an empty final evaluation state. |
| **3** | Logical Error | Reference to an unassigned or undeclared variable. |

---

## Compiling the Code

This project is written using standard C++11 library components and does not require any external dependencies. You can compile it using any standard C++ compiler like `g++`:

```bash
g++ -std=c++11 main.cpp -o expression_solver
