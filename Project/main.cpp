
#include "tokenizer.cpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;
    
/*Run With:
clang++ -std=c++17 main.cpp;
./a.exe --test
or
./a.exe
*/
int main(int argc, char* argv[]) {
    if (argc > 1 && std::string(argv[1]) == "--test") {
        test_tokenize();
        return 0;
    }
    string equation;
    while(true) {
        cout << "Enter equation or 'exit':" << endl << ">";
        getline(cin, equation);
        if (equation == "exit"){
            break;
        }
        try {
            vector<Token> tokens = tokenize(equation);    
        } catch (const invalid_argument& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }
return 0;
}
