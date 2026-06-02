#pragma once

#include <string>
#include <vector>

int getPrecedence(char op);
bool isOperator(char c);
double applyOperator(char op, double a, double b);
std::vector<std::string> infixToPostfix(const std::string& expr);
double evaluatePostfix(const std::vector<std::string>& postfix);
double evaluate(const std::string& expr);
void printPostfix(const std::string& expr);

