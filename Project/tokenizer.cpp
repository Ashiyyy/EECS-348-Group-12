#include <vector>
#include <string>
using namespace std;

class Tokenizer {
    public:
        vector<char> tokens;
        Tokenizer(string s) {
            for (char c: s) {
                tokens.push_back(c);
            }
        }
};