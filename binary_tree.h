
#include <string>
#include "cfg.h"

typedef struct node {
    char op;
    char var[2];
    node *left_child = nullptr;
    node *right_child = nullptr;

    // Struct constructor
    node() 
        : op('\0'), var(""), left_child(nullptr), right_child(nullptr) {} 
    node(char op, float value)
        : op(op), var(""), left_child(nullptr), right_child(nullptr) {}
} Node;

class BTree {
    private:
        // Data Variables 
        Node head;

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

            if(i == 0 && current_node == &head) {
                
                pushLeft(current_node);
                result = buildNode(current_node->left_child, equation, i);
                
                if(result != equation.size() - 1) {
                    pushRight(current_node);
                    buildNode(current_node->right_child, equation, result+1);
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
                    if(jump_condition) {      // indexed variable (x1, x2, y1, a1, ...)
                        current_node->var[0] = equation[i];  
                        current_node->var[1] = equation[i+1];  
                        return i;
                    } else { // Non-indexed variable (x, y, a, b, ...)
                        current_node->var[0] = equation[i];
                        return i;
                    }
                }
            } else if(matchSymbols(equation[i])) {
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
        }
};

