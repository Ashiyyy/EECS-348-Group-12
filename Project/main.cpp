
#include "operators.cpp"
#include "parser.cpp"
#include "tokenizer.cpp"
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::cin;

//takes input and runs program
int main() {
    string equation;
    while(true){
        cout << "Enter the equation, input 'exit' to exit:";
        cout << ">";
        getline(cin, equation);
        if (equation == "exit"){
            break;
        }
        
        //tokenizer
        extern Tokenizer t;
        t = Tokenizer(equation);
        extern vector<char> equation_vector;
        equation_vector = t.tokens;
        
    }
return 0;
}