#include <vector>
#include <string>
#include <cassert>
#include <variant>
#include <iostream>

using namespace std;

class Number {
public:
    int value;
    Number(int v) : value(v) {}
    bool operator==(const Number& other) const {
        return value == other.value;
    }
};

class LeftParen {
public:
    LeftParen() {}
    bool operator==(const LeftParen& other) const {
        return true;
    }
};

class RightParen {
public:
    RightParen() {}
    bool operator==(const RightParen& other) const {
        return true;
    }
};

class Plus {
public:
    Plus() {}
    bool operator==(const Plus& other) const {
        return true;
    }
};

class Minus {
public:
    Minus() {}
    bool operator==(const Minus& other) const {
        return true;
    }
};

class Multiply {
public:
    Multiply() {}
    bool operator==(const Multiply& other) const {
        return true;
    }
};

class Divide {
public:
    Divide() {}
    bool operator==(const Divide& other) const {
        return true;
    }
};

class Exponent {
public:
    Exponent() {}
    bool operator==(const Exponent& other) const {
        return true;
    }
};

using Token = variant<Number, Plus, Minus, Divide, Exponent, Multiply, LeftParen, RightParen>;

vector<Token> tokenize(string equation) {
    vector<Token> tokens;
    equation.erase(remove(equation.begin(), equation.end(), ' '), equation.end());
    for (int i = 0; i < equation.size(); i++) {
        if (equation[i] == '+') {
            tokens.push_back(Plus());
        } else if (equation[i] == '-') {
            tokens.push_back(Minus());
        } else if (equation[i] == '*') {
            tokens.push_back(Multiply());
        } else if (equation[i] == '/') {
            tokens.push_back(Divide());
        } else if (equation[i] == '^') {
            tokens.push_back(Exponent());
        } else if (equation[i] == '(') {
            tokens.push_back(LeftParen());
        } else if (equation[i] == ')') {
            tokens.push_back(RightParen());
        } else if (isdigit(equation[i])) {
            int number = equation[i] - '0';
            tokens.push_back(Number(number));
        } else {
            throw invalid_argument("Syntax Error: " + string(1, equation[i]) + " at position " + to_string(i));
        }
    }
    return tokens;
}

void test_numbers_tokenize() {
    vector<Token> expected = { Number(1) };
    vector<Token> result = tokenize("1");
    assert(expected == result);
}

void test_binary_ops_tokenize() {
    vector<Token> expected = { Plus(), Minus(), Multiply(), Divide(), Exponent() };
    vector<Token> result = tokenize("+-*/^");
    assert(expected == result);
}

void test_parenthesis_tokenize() {
    vector<Token> expected = { LeftParen(), Number(3), RightParen() };
    vector<Token> result = tokenize("(3)");
    assert(expected == result);
}

void test_syntax_error() {
    try {
        tokenize("a");
        assert(false);
    } catch (const invalid_argument& e) {
        string error_message = e.what();
        assert(error_message == "Syntax Error: a at position 0");
    }
}

void test_tokenize_handles_white_space() {
    vector<Token> expected = { Number(1), Plus(), Number(2) };
    vector<Token> result = tokenize("1 + 2");
    assert(expected == result);
}

void test_tokenize() {
    test_numbers_tokenize();
    test_binary_ops_tokenize();
    test_parenthesis_tokenize();
    test_syntax_error();
}
