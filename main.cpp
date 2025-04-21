
#include<iostream>
#include<string>
#include "binary_tree.h"
#include "cfg.h"

int main(int argc, char const *argv[]) {
    
    // std::string equation = "((a*b)-(c*d))/(e*f)+x1+cos(b)*root(f,sin(x1*x2))";
    std::string equation = "x1+a";
    bool equation_result = cfg_checker(equation);
    std::cout << "Equation(" << equation << ") is valid? " << (equation_result ? "True" : "False") << std::endl; 
    BTree eq_tree(equation);

    return 0;
}
