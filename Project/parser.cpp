#include "operators.cpp"
#include <vector>

using namespace std;

class ASTNode {

};

class NumberNode: ASTNode {
    double num;
};

class AdditionNode: ASTNode {
    char add = '+';
};

class SubstractionNode: ASTNode {
    char substract = '-';
};

class DivisionNode: ASTNode {
    char substract = '/';
};

class MultiplicationNode: ASTNode {
    char substract = '*';
};

class ModulusNode: ASTNode {
    char substract = '%';
};

class ExponentNode: ASTNode {
    char substract = '^';
};

//Expects a vector or list of class Token
class Parser {
    public:
        void parse(vector<char> token_vec) {
            vector<char> list;
            while (token_vec.size() > 0) {
                int i = 0;
            }
        }
};

// We decided to also calulate the output in parser (or not in main). Don't worry about doing that part Marren