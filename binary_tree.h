
#include <string>

typedef struct node {
    char op;
    float value;
    node *left_child = nullptr;
    node *right_child = nullptr;

    // Struct constructor
    node() 
        : op('\0'), value(0.0f), left_child(nullptr), right_child(nullptr) {} 
    node(char op, float value)
        : op(op), value(value), left_child(nullptr), right_child(nullptr) {}
} Node;

class BTree {
    private:
        // Data Variables 
        Node head;

    public:        
        BTree(std::string equation) {
            unsigned index = 0;

            // Sets the first two child nodes for the most simple equation (such as a+b)
            pushLeft(&head); pushRight(&head);
            
            // Left side of the tree
            buildNode(head.left_child, equation, &index);

            // Right side of the tree
            buildNode(head.right_child, equation, &index);
        }
        
        void pushLeft(Node *current_node) { current_node->left_child = new Node(); }
        void pushLeft(Node *current_node, char op, float value) { current_node->left_child = new Node(op, value); }
        
        void pushRight(Node *current_node) { current_node->right_child = new Node(); }
        void pushRight(Node *current_node, char op, float value) { current_node->right_child = new Node(op, value); }
        
        void buildNode(Node *current_node, std::string equation, unsigned *index) {
            
        }
};

typedef struct map {
    int position;
    char *value;
} Map;

int charType(std::string equation, int index) {
    /* 
        0 -> parte de variável 
        1 -> operadores simples (+, -, *, /)
        2 -> operadores complexos 1 (^, root())
        3 -> operadores complexos 2 (sen, cos, tan)
        4 -> parenteses aberto
        5 -> parenteses fechado
    */

    char c = equation[index];
    std::string aux_string;
    int i;

    // Checks for variable names
    if ((c >= '1' && c <= '0') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))  {
        aux_string += c;                                            // Starts the variable string
        if(c != 'c' && c != 't' && c != 's' && c != 'e') {
            return 0;
        } else {
            // Checks the next characters to find 'sen', 'cos', 'tan' and 'root' occurences 
            //    or composite variable names (such as a1, xn, an so on) 
            while(index < equation.length() && charType(equation, index + 1) == 0) {
                aux_string += equation[index + 1];                  
                index += 1;
            }

            if(aux_string == "sen" || aux_string == "cos" || aux_string == "tan") {
                return 3;            
            } else if(aux_string == "exp") {
                return 2;
            } else {
                return 0;
            }

        }
    } else if(c == '+' || c == '-' || c == '*' || c == '/') {
        return 1;
    } else if(c == '^') {
        return 2;
    } else if(c == '(') {
        return 4;
    } else if(c == ')') {
        return 5;
    }
}
