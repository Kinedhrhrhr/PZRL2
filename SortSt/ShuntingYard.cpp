#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <cmath>
#include <cctype>
#include "ShuntingYard.h"

int getPrecedence(char op) 
{
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

bool isOperator(char c) 
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

double applyOperator(char op, double a, double b) 
{
    switch (op) 
    {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '^': return pow(a, b);
        default: return 0;
    }
}

std::vector<std::string> infixToPostfix(const std::string& expr) 
{
    std::stack<char> ops;
    std::vector<std::string> output;
    
    for (size_t i = 0; i < expr.length(); i++) 
    {
        char c = expr[i];    
        if (std::isspace(c)) continue;      
	if (std::isdigit(c) || c == '.') 
        {
            std::string num;
            while (i < expr.length() && (std::isdigit(expr[i]) || expr[i] == '.')) 
            {
                num += expr[i];
                i++;
            }
            output.push_back(num);
            i--;
        }
	else if (c == '(') 
        {
            ops.push(c);
        }
        else if (c == ')') 
        {
            while (!ops.empty() && ops.top() != '(') 
            {
                output.push_back(std::string(1, ops.top()));
                ops.pop();
            }
            if (!ops.empty()) ops.pop();
        }
        else if (isOperator(c)) 
        {
            while (!ops.empty() && ops.top() != '(' && getPrecedence(ops.top()) >= getPrecedence(c)) 
            {
                if (c == '^' && ops.top() == '^') break;
                output.push_back(std::string(1, ops.top()));
                ops.pop();
            }
            ops.push(c);
        }
    }
    while (!ops.empty()) 
    {
        output.push_back(std::string(1, ops.top()));
        ops.pop();
    }
    return output;
}

double evaluatePostfix(const std::vector<std::string>& postfix) 
{
    std::stack<double> values;
    
    for (const std::string& token : postfix) 
    {
        if (token.length() == 1 && isOperator(token[0])) 
        {
            double b = values.top(); 
            values.pop();
            double a = values.top(); 
            values.pop();
            values.push(applyOperator(token[0], a, b));
        } 
        else 
        {
            values.push(std::stod(token));
        }
    } 
    return values.top();
}

double evaluate(const std::string& expr) 
{
    std::vector<std::string> postfix = infixToPostfix(expr);
    return evaluatePostfix(postfix);
}

void printPostfix(const std::string& expr) 
{
    std::vector<std::string> postfix = infixToPostfix(expr);
    for (const std::string& s : postfix) 
    {
        std::cout << s << " ";
    }
}
