
#include <string>
#include <iostream>
#include <vector>

bool matchDigit(char item) { return (item >= '0' && item <='9'); }

bool matchLetter(char item) { return ((item >= 'a' && item <= 'z') || (item >= 'A' && item <= 'Z')); }

bool matchSymbols(char item) { return (
    item == '+' || item == '-' || item == '/' || item == '*' || item == '^'); }

void matchOperations(std::string &equation) {
    std::string operation = "cos";
    int result = 0;
    
    while(result != -1) {
        result = equation.find(operation);
        if(result != -1) {
            equation.replace(result, result + operation.length() - 1, "_");
        } else {
            if(operation == "cos") {
                operation = "sin"; result = 0;
            } else if(operation == "sin") {
                operation = "tan"; result = 0;
            } else if(operation == "tan") {
                operation = "root"; result = 0;
            }
        }
    }
}

void C(std::string &equation) {

    // C -> Variables and constants
    std::size_t output = equation.find("&");
    
    while(output != std::string::npos) {
        
        if(output != equation.length()-1 && equation[output+1] == '$')
            equation.replace(output, output+1, "C");
        else
            equation[output] = 'C';
        
        output = equation.find("&");
    }
}

void A(std::string &equation) {
    std::vector<std::string> A_transformations = {"ABA", "(A)", "cos(A)", "sin(A)", "tan(A)", "root(A, A)"};
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
                std::cin >> foo;
                result = equation.find(A_transformations[i]);
                iteration_counter++;
            }
        }
    }while(iteration_counter != 0);
}

bool cfg_checker(std::string equation, bool show_prints = false) {

    std::cout << equation << "\n" << matchLetter('(') << std::endl;    

    for(int i = 0; i < equation.length(); i++) {
        std::cout << (matchDigit(equation[i]));
        if(matchDigit(equation[i]))
            equation[i] = '$';
    }
    std::cout << std::endl << equation << std::endl;
    for(int i = 0; i < equation.length(); i++) {
        std::cout << (matchLetter(equation[i]));
        if(matchLetter(equation[i]))
            equation[i] = '&';
    }
    std::cout << std::endl << equation << std::endl;
    for(int i = 0; i < equation.length(); i++) {
        std::cout << (matchSymbols(equation[i]));
        if(matchSymbols(equation[i]))
            equation[i] = 'B';
    }
    std::cout << std::endl << equation << std::endl;    
    
    C(equation);
    A(equation);

    std::cout << equation << std::endl;

    return (equation == "A");
}
