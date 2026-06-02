#include <iostream>
#include <string>
#include "ShuntingYard.h"

int main() 
{
    std::string tests[] = {"3+4*2/(1-5)", "(3+4)*5", "2^3^2", "3.5+4.2*2"};
    for (std::string s : tests) 
    {
        std::cout << s << " => ";
        printPostfix(s);
        std::cout << "  = " << evaluate(s) << std::endl;
    }
    
    std::string input;
    std::cout << "Введите выражение: ";
    std::getline(std::cin, input);
    if (!input.empty()) 
    {
        std::cout << "Результат: " << evaluate(input) << std::endl;
    }
    
    return 0;
}
