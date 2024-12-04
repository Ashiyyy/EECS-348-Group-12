#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

//enumerate token types
enum class TokenType { Number, Plus, Minus, Multiply, Divide, Exponent, LeftParen, RightParen, Modulo};

/*
    Token struct:
        - type: the type of the token
        - value: the optional value for a constant, default 0
*/
struct Token {
    TokenType type;
    float value;
    //polymorphic comparison
    bool operator==(const Token& other) const {
        return type == other.type && value == other.value;
    }
};

//tokenize declaratin
vector<Token> tokenize(string equation);

//tokenize test declarations
void test_tokenize();

#endif