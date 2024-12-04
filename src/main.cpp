#include <iostream>
#include <string>
#include <vector>
#include "tokenizer.h"
#include "parser.h"
#include "evaluator.h"

using namespace std;

/* Run With:
   make
   ./calculator.exe
   make --test
   make run
*/
int main(int argc, char* argv[]) {
    //configuration to allow running tests easily
    if (argc > 1 && std::string(argv[1]) == "--test") {
        try {
            test_tokenize();
            test_parser();
            cout << "All tests passed." << endl;
        //catch errors found in tests
         } catch (const std::exception& e) {
            cerr << "Error in Tests: " << e.what() << endl;
        }
        return 0;
    }
    //create a buffer to hold user input
    string buffer;
    //prompt user for input
    cout << "Enter equation or 'exit':" << endl << "> ";
    while (true) {
        getline(cin, buffer);
        if (buffer == "exit"){
            break;
        }
        try {
            //tokenize the input
            vector<Token> tokens = tokenize(buffer);
            //parse the tokens into an abstract syntax tree
            ASTNode ast = parse(tokens);
            //evaluate the abstract syntax tree
            float result = evaluate(ast);
            cout << result << endl;
        //catch errors to prevent a crash
        } catch (const std::exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
        cout << "> ";
    }
    return 0;
}
