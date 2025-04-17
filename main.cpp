
#include<iostream>
#include<string>
// #include "binary_tree.h"
#include "cfg.h"

int main(int argc, char const *argv[]) {
    
    std::string equation = "((a*b)-(c*d))/(e*f)+x1+cos(b)*root(f,sin(x1*x2))";
    std::cout << cfg_checker(equation) << std::endl; 

    return 0;
}
