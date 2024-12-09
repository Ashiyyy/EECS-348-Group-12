#include <vector>
#include <string>
#include <cassert>
#include <variant>
#include <iostream>
#include "tokenizer.h"
#include <algorithm>

#ifndef TOKENIZER_CPP
#define TOKENIZER_CPP

using namespace std;

//tokenize validates a string input and creates a token stream
vector<Token> tokenize(string equation) {
    vector<Token> tokens;
    //remove all white space
    equation.erase(std::remove(equation.begin(), equation.end(), ' '), equation.end());
    //for each char
    for (int i = 0; i < equation.size(); i++) {
        char c = equation[i];
        //match char
        if (c == '+') {
            tokens.push_back({TokenType::Plus, 0});
        } else if (c == '%') {
            tokens.push_back({TokenType::Modulo, 0});
        } else if (c == '-') {
            tokens.push_back({TokenType::Minus, 0});
        } else if (c == '*') {
            //determine if its exponent or multiplication by checking the next char
            if (i + 1 < equation.size() && equation[i + 1] == '*') {
                tokens.push_back({TokenType::Exponent, 0});
                i++;
            //if its not exponent, push multiplication
            } else {
                tokens.push_back({TokenType::Multiply, 0});
            }
        } else if (c == '/') {
            tokens.push_back({TokenType::Divide, 0});
        } else if (c == '^') {
            tokens.push_back({TokenType::Exponent, 0});
        } else if (c == '(') {
            tokens.push_back({TokenType::LeftParen, 0});
        } else if (c == ')') {
            tokens.push_back({TokenType::RightParen, 0});
        //if constant number
        } else if (isdigit(c) || c == '.') {
            int start = i;
            bool has_decimal = false;
            //check for decimals
            while (i < equation.size() && (isdigit(equation[i]) || equation[i] == '.')) {
                if (equation[i] == '.') {
                    if (has_decimal) { //found a second decimal point
                        throw invalid_argument("Syntax: Multiple decimals points");
                    }
                    has_decimal = true;
                }
                i++;
            }
            string number_str = equation.substr(start, i - start);
            //use stod to turn string into double
            double number = stod(number_str);
            //cast double to float
            tokens.push_back({TokenType::Number, static_cast<float>(number)});
            i--;
        } else {
            throw invalid_argument("Syntax Error: " + string(1, c) + " at position " + to_string(i));
        }
    }
    return tokens;
}

void test_numbers_tokenize() {
    //test tokenize "1"
    vector<Token> expected = { {TokenType::Number, 1} };
    vector<Token> result = tokenize("1");
    assert(expected == result);
}

void test_binary_ops_tokenize() {
    //test tokenize "+-*/^"
    vector<Token> expected = {
        {TokenType::Plus, 0},
        {TokenType::Minus, 0},
        {TokenType::Multiply, 0},
        {TokenType::Divide, 0},
        {TokenType::Exponent, 0}
    };
    vector<Token> result = tokenize("+-*/^");
    assert(expected == result);
}

void test_three_digit_numbers_tokenize() {
    //test tokenize "123+456*789"
    vector<Token> expected = {
        {TokenType::Number, 123},
        {TokenType::Plus, 0},
        {TokenType::Number, 456},
        {TokenType::Multiply, 0},
        {TokenType::Number, 789}
    };
    vector<Token> result = tokenize("123+456*789");
    assert(expected == result);
}

void test_parenthesis_tokenize() {
    //test tokenize "(3)"
    vector<Token> expected = {
        {TokenType::LeftParen, 0},
        {TokenType::Number, 3},
        {TokenType::RightParen, 0}
    };
    vector<Token> result = tokenize("(3)");
    assert(expected == result);
}

void test_exponent_tokenize() {
    //test tokenize "2**3"
    vector<Token> expected = {
        {TokenType::Number, 2},
        {TokenType::Exponent, 0},
        {TokenType::Number, 3}
    };
    vector<Token> result = tokenize("2**3");
    assert(expected == result);
}

void test_syntax_error() {
    //test tokenize "a" expecting caught exception
    try {
        tokenize("a");
        assert(false);
    } catch (const invalid_argument& e) {
        string error_message = e.what();
        assert(error_message == "Syntax Error: a at position 0");
    }
}

void test_tokenize_handles_white_space() {
    //test tokenize "1 + 2"
    vector<Token> expected = {
        {TokenType::Number, 1},
        {TokenType::Plus, 0},
        {TokenType::Number, 2}
    };
    vector<Token> result = tokenize("1 + 2");
    assert(expected == result);
}

void test_modulo_tokenize() {
    //test tokenize "10%3"
    vector<Token> expected = {
        {TokenType::Number, 10},
        {TokenType::Modulo, 0},
        {TokenType::Number, 3}
    };
    vector<Token> result = tokenize("10%3");
    assert(expected == result);
}

void test_decimal_tokenize() {
    //test tokenize "3.14+2.5"
    vector<Token> expected = {
        {TokenType::Number, 3.14},
        {TokenType::Plus, 0},
        {TokenType::Number, 2.5}
    };
    vector<Token> result = tokenize("3.14+2.5");
    assert(expected == result);
}

//run all tokenizer tests
void test_tokenize() {
    test_numbers_tokenize();
    test_binary_ops_tokenize();
    test_parenthesis_tokenize();
    test_syntax_error();
    test_tokenize_handles_white_space();
    test_exponent_tokenize();
    test_modulo_tokenize();
    test_decimal_tokenize();
}

#endif
