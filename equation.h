
#include <string>
#include <stack>
#include <map>
#include <iostream>
#include <math.h>
#include "utils.h"
#include "binary_tree.h"
#include "cfg.h"

class Equation {
    private:
        std::string equation;
        std::stack<SNode> execution_stack;
        std::map<std::string, double> dynamic_variables;
        std::map<std::string, double> static_variables;
    public:
        Equation(std::string new_equation) {
            this->equation = new_equation;

            preProcessing();
        }

        double compute(double reg_1, double reg_2, char op_reg) {
            switch (op_reg) {
                case '+':
                    return reg_1 + reg_2;       
                    break;
                
                case '-':
                    return reg_1 - reg_2;
                    break;

                case '/':
                    return reg_1 / reg_2;
                    break;

                case '*':
                    return reg_1 * reg_2;
                    break;

                case '^':
                    return pow(reg_1, reg_2);
                    break;

                case 's':
                    return sin(reg_1);
                    break;

                case 'c':
                    return cos(reg_1);
                    break;

                case 't':
                    return tan(reg_1);
                    break;

                case 'r':
                    return pow(reg_1, 1/reg_2);
                    break;

            }
        }

        void preProcessing(bool debug = false) {
            if(cfg_checker(this->equation)) {
                BTree eq_tree(equation);
                execution_stack = eq_tree.TreeToStack();
            }

        }   
        void process(bool debug = false) {
            std::string reg_1, reg_2, 
                       *cur_reg = &reg_1;
            char op_reg;
            
            while(execution_stack.size() != 0) {
                if(execution_stack.top().op != ' ') {
                    op_reg = execution_stack.top().op;   
                    execution_stack.pop();
                    compute(reg_1, reg_2, op_reg);
                } else {
                    *cur_reg = execution_stack.top().var;
                    cur_reg = cur_reg == &reg_1 ? &reg_2 : &reg_1;
                }
                execution_stack.pop();
            }
        }
};
