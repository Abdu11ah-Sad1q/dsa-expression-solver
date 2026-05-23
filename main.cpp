#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <stack>
#include <algorithm>
#include <limits> 

using namespace std;

// Checks if character is a valid math symbol
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Standard operator precedence logic
int getPrecedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

bool isOpeningBracket(char c) {
    return (c == '(' || c == '[' || c == '{');
}

bool isClosingBracket(char c) {
    return (c == ')' || c == ']' || c == '}');
}

// Bracket matching check
bool matches(char open, char close) {
    return (open == '(' && close == ')') || 
           (open == '[' && close == ']') || 
           (open == '{' && close == '}');
}
int main(){
  return 0;
}
