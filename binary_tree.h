
#include <string>
#include <vector>
#include <iostream>
#include "utils.h"

class BTree {
    private:
        // Data Variables 
        Node head;

        void printNode(Node *node, unsigned i) {
            for(int j = 0; j < i; j++) { std::cout << ' '; }
            std::cout << "op: " << node->op << ", var: " << node->var << std::endl;
            if(node->left_child != nullptr) { printNode(node->left_child, i+4); }
            if(node->right_child != nullptr) { printNode(node->right_child, i+4); }
        }

    public:        
        BTree(std::string equation) {
            unsigned index = 0;

            buildNode(&head, equation, index);
        }
        
        void pushLeft(Node *current_node) { current_node->left_child = new Node(); }
        void pushLeft(Node *current_node, char op, float value) { current_node->left_child = new Node(op, value); }
        
        void pushRight(Node *current_node) { current_node->right_child = new Node(); }
        void pushRight(Node *current_node, char op, float value) { current_node->right_child = new Node(op, value); }
        
        unsigned buildNode(Node *current_node, std::string equation, unsigned i) {
            
            std::vector<std::string> reserved_words = {"cos", "sin", "tan", "root"};
            std::size_t result;
            unsigned return_i_left, return_i_right;
            bool jump_condition;

            std::cout << "Step " << i <<", equation[" << i << "] = " << equation[i] << std::endl;

            printTree();

            if(i == 0 && current_node == &head) {
                
                pushLeft(current_node);
                result = buildNode(current_node->left_child, equation, i);
                
                if(result < equation.size()) {
                    pushRight(current_node);
                    result = buildNode(current_node, equation, result); 
                    printf("result: %d, head_detection: %d\n", result, (current_node == &head));
                } else {
                    head = *head.left_child;
                }
            } else if(matchLetter(equation[i])) {
                for(int j = 0; j < reserved_words.size(); j++) {

                    result = equation.substr(i).find(reserved_words[j]); 
                    
                    if(result != std::string::npos) {
                        current_node->op = reserved_words[i][0];
                        pushLeft(current_node);
                        return buildNode(current_node->left_child, equation, i + 2); // Jumps the '(' character
                    }
                }
                
                // If there were no substrings operations found
                jump_condition = (i + 1) < equation.length() && matchDigit(equation[i+1]); 
                if(result == std::string::npos) {
                    // printf("jump_condition, %d\n", i);
                    if(jump_condition) {      // indexed variable (x1, x2, y1, a1, ...)
                        // printf("jump_condition = true, %d\n", i);
                        current_node->var[0] = equation[i];  
                        current_node->var[1] = equation[i+1];  
                        return i+2;
                    } else { // Non-indexed variable (x, y, a, b, ...)
                        // printf("jump_condition = false, %d (node_exists = %d, r_child = %d)\n", 
                        //        i, (current_node == nullptr), (current_node == head.right_child));
                        current_node->var[0] = equation[i];
                        // printf("Over\n");
                        return i+1;
                    }
                    // printf("jump_condition finished, %d\n", i);
                }
            } else if(matchSymbols(equation[i])) {
                // printf("Symbol detected, %c, %d\n", equation[i], i);
                current_node->op = equation[i];
                pushRight(current_node);
                return buildNode(current_node->right_child, equation, i+1);
            } else {
                pushLeft(current_node);
                return_i_left = buildNode(current_node->left_child, equation, i+1);
                pushRight(current_node);
                current_node->op = equation[return_i_left + 1];
                return buildNode(current_node->right_child, equation, return_i_left+2);
            }
            printTree();
            return result;
        }

        void printTree() { printNode(&head, 0); }
};