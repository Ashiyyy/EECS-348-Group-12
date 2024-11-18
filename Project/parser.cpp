#include "operators.cpp"
#include <vector>

class ASTNode {

}

class NumberNode: ASTNode {
    double num;
}

class AdditionNode: ASTNode {

}

//Expects a vector or list of class Token

class Parser {
    public:
        void parse(std::vector<Token> token_vec;) {
            std::vector<Token> stack;  
            while token_vec.len() > 0 {

            } 

        }
}

// We decided to also calulate the output in parser (or not in main). Don't worry about doing that part Marren