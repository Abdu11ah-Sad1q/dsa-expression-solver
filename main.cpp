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

// Asks the user for variable values via console
void getValues(vector<long long>& values, const vector<string>& variables) {
    values.resize(variables.size()); 
    for (int i = 0; i < variables.size(); i++) {
        // Strict constraint: Prompts must go to stderr, not stdout!
        cerr << "Enter value for " << variables[i] << ": ";
        
        // Input validation fallback
        while (!(cin >> values[i])) { 
            cerr << "Invalid input. Please enter a number for " << variables[i] << " : ";
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
        // cout << '\n';
    }
}

// Scans our vectors to fetch a variable's assigned integer value
long long findValue(const vector<string>& variables, const vector<long long>& values, const string& x) {
    for (int i = 0; i < variables.size(); i++) {
        if (variables[i] == x) {
            return values[i];
        }
    }
    cerr << "Logical Error: Reference to unassigned variable: " << x << "\n";
    exit(3); // Logical error exit code
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

// Evaluates the postfix token structure mathematically
long long evaluatePostfixExpression(const vector<string>& postfixTokens, const vector<string>& variables, const vector<long long>& values) {
    stack<long long> evalStack; 

    for (int i = 0; i < postfixTokens.size(); i++) {
        // If token is a single-character operator
        if (isOperator(postfixTokens[i][0]) && postfixTokens[i].length() == 1) {
            char currentOp = postfixTokens[i][0];

            if (evalStack.empty()) {
                cerr << "Syntax Error: Insufficient operands for operation.\n";
                exit(1);
            }
            long long val2 = evalStack.top();
            evalStack.pop();

            if (evalStack.empty()) {
                cerr << "Syntax Error: Insufficient operands for operation.\n";
                exit(1);
            }
            long long val1 = evalStack.top();
            evalStack.pop();

            long long result = 0;
            if (currentOp == '+') result = val1 + val2;
            else if (currentOp == '-') result = val1 - val2;
            else if (currentOp == '*') result = val1 * val2;
            else if (currentOp == '/') {
                if (val2 == 0) {
                    cerr << "Runtime Error: Division by zero encountered.\n";
                    exit(2); // Runtime error exit code
                }
                result = val1 / val2;
            }
            evalStack.push(result);
        }
        // If token is a number string
        else if (isdigit(postfixTokens[i][0])) {
            evalStack.push(stoi(postfixTokens[i]));
        }
        // Must be a variable string
        else {
            long long val = findValue(variables, values, postfixTokens[i]);
            evalStack.push(val);
        }
    }

    if (evalStack.empty()) {
        cerr << "Runtime Error: Evaluation yielded empty final state.\n";
        exit(2);
    }
    
    long long finalOutput = evalStack.top();
    evalStack.pop();

    if (!evalStack.empty()) {
        cerr << "Syntax Error: Extraneous operands remaining.\n";
        exit(1);
    }

    return finalOutput;
}

int main() {
    string infixExpression;
     cerr << "Enter the expression: ";
    if (!getline(cin, infixExpression)) {
        return 0;
    }

    vector<string> variables;
    vector<long long> values;

    // Run conversion pass
    vector<string> postfixTokens = convertInfixToPostfix(infixExpression, variables);

    // Prompt user for input values via stderr stream
    getValues(values, variables);

    // Compute stack results
    long long finalEvaluation = evaluatePostfixExpression(postfixTokens, variables, values);

    // Printing output tokens safely without adding a messy trailing space
    for (int i = 0; i < postfixTokens.size(); i++) {
        cout << postfixTokens[i];
        if (i + 1 < postfixTokens.size()) {
            cout << " ";
        }
    }
    cout << "\n";
    cout << finalEvaluation << "\n";

    return 0; // Everything ran cleanly!
}
