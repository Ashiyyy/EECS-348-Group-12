#include <vector>
#include <string>
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
            string legal = "1234567890()*/+-";
            string operators = "*()-+/";
            bool valid = true;
            int t = string::npos;
            int i;
            int count = 0;

            //checks that every char is valid in a math expression
            try {
                for(i = 0; i < input.length(); i++) {
                    char c = input.substr(i, 1)[0];
                    if(legal.find(c) == t) {
                        valid = false;
                    } else if (operators.find(c) == t && operators.find(input.substr(i + 1, 1)[0] == t)) {
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