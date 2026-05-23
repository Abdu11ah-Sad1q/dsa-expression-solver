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

// Converts standard expression to Reverse Polish Notation (Tokens)
vector<string> convertInfixToPostfix(const string& infix, vector<string>& variables) {
    stack<char> operatorStack; 
    vector<string> postfixTokens; 
    int i = 0;
    int len = infix.length();

    while (i < len) {
        if (isspace(infix[i])) {
            i++;
            continue;
        }

        // Grabbing multi-digit whole numbers
        if (isdigit(infix[i])) {
            string num = "";
            while (i < len && isdigit(infix[i])) {
                num += infix[i];
                i++;
            }
            postfixTokens.push_back(num);
            continue;
        }

        // Grabbing legal C++ variable names (allows letters/underscores/digits)
        if (isalpha(infix[i]) || infix[i] == '_') {
            string var = "";
            while (i < len && (isalnum(infix[i]) || infix[i] == '_')) {
                var += infix[i];
                i++;
            }
            postfixTokens.push_back(var);
            // Track uniquely found variables to query them later
            if (find(variables.begin(), variables.end(), var) == variables.end()) {
                variables.push_back(var);
            }
            continue;
        }

        if (isOpeningBracket(infix[i])) {
            operatorStack.push(infix[i]);
            i++;
            continue;
        }

        if (isClosingBracket(infix[i])) {
            bool foundMatch = false;
            while (!operatorStack.empty()) {
                char topOp = operatorStack.top();
                if (isOpeningBracket(topOp)) {
                    if (matches(topOp, infix[i])) {
                        foundMatch = true;
                        operatorStack.pop();
                    }
                    break;
                }
                postfixTokens.push_back(string(1, topOp));
                operatorStack.pop();
            }
            if (!foundMatch) {
                cerr << "Syntax Error: Mismatched grouping symbols.\n";
                exit(1); // Syntax error exit code
            }
            i++;
            continue;
        }

        if (isOperator(infix[i])) {
            while (!operatorStack.empty() && !isOpeningBracket(operatorStack.top()) &&
                   getPrecedence(operatorStack.top()) >= getPrecedence(infix[i])) {
                postfixTokens.push_back(string(1, operatorStack.top()));
                operatorStack.pop();
            }
            operatorStack.push(infix[i]);
            i++;
            continue;
        }

        cerr << "Syntax Error: Illegal character in expression.\n";
        exit(1);
    }

    // Dump out remaining stacked operators
    while (!operatorStack.empty()) {
        char topOp = operatorStack.top();
        if (isOpeningBracket(topOp)) {
            cerr << "Syntax Error: Unclosed grouping bracket detected.\n";
            exit(1);
        }
        postfixTokens.push_back(string(1, topOp));
        operatorStack.pop();
    }

    return postfixTokens;
}

int main() {
    string infixExpression;
    cerr << "Enter the expression: ";
    if (!getline(cin, infixExpression)) {
        return 0;
    }
    vector<string> variables;
    vector<string> postfixTokens = convertInfixToPostfix(infixExpression, variables);
    return 0;
}
