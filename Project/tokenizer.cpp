#include <vector>
#include <string>
#include <regex>
#include <iterator>
#include <stack>
using namespace std;

class Tokenizer {
    public:
        vector<char> tokens;
        string input;

        Tokenizer(string s) {
            input = s;
        }

        vector<char> getTokens() {
            for (char c: input) {
                tokens.push_back(c);
            }
            return tokens;
        }

        bool isValid() {
            string legal = "1234567890()*/+-%";
            string operators = "*()-+/%";
            bool valid = true;
            int i;
            int count = 0;
            std::regex regex ("\\*\\*")

            //checks that every char is valid in a math expression
            try {
                //replacing ** with ^
                input = regex_replace(input,regex,"^");
            
            int pop_length = input.length();
            for (i = 0; i < pop_length; i++) {
                char c = input.substr(i , 1)[0];
                if (c == '*'){
                    if (input.substr(i + 1, 1)[0] == '*'){
                        input.pop(i+1)
                        input[i] = '^';
                        pop_length--;
                    }
                }
            }
                
            for(i = 0; i < input.length(); i++) {
                char c = input.substr(i, 1)[0];
                if(legal.find(c) == string::npos) {
                    valid = false;
                } else if (operators.find(c) == string::npos && operators.find(input.substr(i + 1, 1)[0] == string::npos)) {
                    valid = false;
                } else if (c == '(') {
                    count++;
                } else if (c == ')') {
                    count--;
                }
            }
            if (count != 0) {
                valid = false;
            }
            } catch(...) {
                valid = false;
            }
            return valid;
        }
};