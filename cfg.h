
#include <string>
#include <iostream>
#include <vector>
#include "utils.h"

void C(std::string &equation) {

    // C -> Variables and constants
    std::size_t output = equation.find("&");
    
    while(output != std::string::npos) {
        
        if(output != equation.length()-1 && equation[output+1] == '$')
            equation.replace(output, 2, "C");
        else
            equation[output] = 'C';
        
        output = equation.find("&");
    }
}

void A(std::string &equation) {
    std::vector<std::string> A_transformations = {"ABA", "(A)", "@A", "@(A,A)"};
    std::size_t result;
    unsigned iteration_counter = 0;
    int foo;

    for(int i = 0; i < equation.length(); i++) 
        if(equation[i] == 'C')
            equation[i] = 'A';
    
    std::cout << equation << std::endl;

    do {
        iteration_counter = 0;
        for(int i = 0; i < A_transformations.size(); i++) {
            result = equation.find(A_transformations[i]);
            while(result != std::string::npos) {
                equation.replace(result, A_transformations[i].length(), "A");
                std::cout << equation << "        Op(" << A_transformations[i] << " - " << 
                          result << ", " << A_transformations[i].length() - 1 << ")" << " - It_c = " 
                          << iteration_counter << std::endl;
                result = equation.find(A_transformations[i]);
                iteration_counter++;
            }
        }
    }while(iteration_counter != 0);
}

void DE(std::string &equation) {
    std::vector<std::string> reserved_words = {"cos", "sin", "tan", "root"};
    std::size_t result;

    for(int i = 0; i < reserved_words.size(); i++) {
        for(int j = 0; j < (equation.length() - reserved_words[i].length()); j++) {
            result = equation.substr(j).find(reserved_words[i]);
            if(result != std::string::npos) {
                equation.replace(result, reserved_words[i].length(), "@");
                std::cout << equation << std::endl;
            }
        }
    }
}

bool cfg_checker(std::string equation, bool show_prints = false) {


    std::cout << equation << std::endl;    

    DE(equation);

    for(int i = 0; i < equation.length(); i++) {
        if(matchDigit(equation[i])) {
            equation[i] = '$';
        }
    }
    std::cout << equation << std::endl;
    for(int i = 0; i < equation.length(); i++) {
        if(matchLetter(equation[i]))
            equation[i] = '&';
    }
    std::cout << equation << std::endl;
    for(int i = 0; i < equation.length(); i++) {
        if(matchSymbols(equation[i]))
            equation[i] = 'B';
    }
    std::cout << equation << std::endl;    
    
    C(equation);
    A(equation);

    return (equation == "A");
}
