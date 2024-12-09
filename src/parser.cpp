#ifndef PARSER_CPP
#define PARSER_CPP

#include <variant>
#include <memory>
#include <vector>
#include <stdexcept>
#include <cassert>
#include <iostream>
#include "parser.h"
#include "tokenizer.h"

using namespace std;

//operator struct
struct Operator {
    TokenType type;
    bool is_unary;
};

pair<int, BinaryOperator> get_binary_operator(TokenType type) {
    //map the operator to the correct enum
    switch (type) {
        case TokenType::Plus:
            return {1, BinaryOperator::Plus};
        case TokenType::Minus:
            return {1, BinaryOperator::Minus};
        case TokenType::Multiply:
            return {2, BinaryOperator::Multiply};
        case TokenType::Divide:
            return {2, BinaryOperator::Divide};
        case TokenType::Exponent:
            return {3, BinaryOperator::Exponent};
        case TokenType::Modulo:
            return {3, BinaryOperator::Modulo};
        default:
            throw runtime_error("Syntax");
    }
}

int get_operator_priority(const Operator& op) {
    //higher is higher priority
    if (op.is_unary) {
        return 4;
    } else {
        switch (op.type) {
            case TokenType::LeftParen:
                return 0;
            case TokenType::Plus:
            case TokenType::Minus:
                return 1;
            case TokenType::Multiply:
            case TokenType::Modulo:
            case TokenType::Divide:
                return 2;
            case TokenType::Exponent:
                return 3;
            default:
                throw runtime_error("Syntax");
        }
    }
}

//Helper function that creates a finished node for the AST
void combine_nodes(vector<ASTNode>& operand_stack, vector<Operator>& operator_stack) {
    if (operator_stack.empty()) { //cant combine nothing
        throw runtime_error("Syntax");
    }
    //get top of stack
    Operator op = operator_stack.back();
    operator_stack.pop_back();
    if (op.is_unary) {
        if (operand_stack.empty()) {
            throw runtime_error("Syntax");
        }
        //get the child node
        ASTNode child = operand_stack.back(); 
        operand_stack.pop_back();
        UnaryOperator unary_op;
        int priority = 4;
        if (op.type == TokenType::Minus) {
            unary_op = UnaryOperator::Negate;
        } else {
            throw runtime_error("Syntax");
        }
        //create the node and put it back on the stack
        operand_stack.push_back(make_shared<UnaryNode>(priority, child, unary_op));
    //if not unary node (so binary)
    } else {
        if (operand_stack.size() < 2) { //need two operands for binary
            throw runtime_error("Syntax: Insufficient operands");
        }
        //get left and right operands
        ASTNode right = operand_stack.back();
        operand_stack.pop_back();
        ASTNode left = operand_stack.back();
        operand_stack.pop_back();
        //get the operator
        auto [priority, bin_op] = get_binary_operator(op.type);
        //create the node and put it back on the stack
        operand_stack.push_back(make_shared<BinaryNode>(priority, left, right, bin_op));
    }
}

//creates an abstract syntax tree from a list of tokens
ASTNode parse(const vector<Token>& tokens) {
    vector<ASTNode> operand_stack;
    vector<Operator> operator_stack;
    //for each token
    for (int i = 0; i < tokens.size(); ++i) {
        //get token
        const auto& token = tokens[i];
        //match token
        switch (token.type) {
            case TokenType::Number:
                operand_stack.push_back(make_shared<NumberNode>(static_cast<float>(token.value)));
                break;
            case TokenType::LeftParen:
                operator_stack.push_back({token.type, false});
                break;
            case TokenType::RightParen:
                //if right paren, find left paren
                while (!operator_stack.empty() && operator_stack.back().type != TokenType::LeftParen) {
                    combine_nodes(operand_stack, operator_stack);
                }
                if (operator_stack.empty() || operator_stack.back().type != TokenType::LeftParen) {
                    throw runtime_error("Syntax: Invalid Parentheses");
                }
                operator_stack.pop_back();
                break;
            case TokenType::Modulo:
            case TokenType::Plus:
            case TokenType::Minus:
            case TokenType::Multiply:
            case TokenType::Divide:
            case TokenType::Exponent: {
                bool is_unary = false;
                //determine if unary with context
                if (token.type == TokenType::Minus) {
                    if (
                        i == 0 || tokens[i - 1].type == TokenType::LeftParen ||
                        tokens[i - 1].type == TokenType::Plus || tokens[i - 1].type == TokenType::Minus ||
                        tokens[i - 1].type == TokenType::Multiply || tokens[i - 1].type == TokenType::Divide ||
                        tokens[i - 1].type == TokenType::Exponent || tokens[i - 1].type == TokenType::Modulo
                        ) {
                        is_unary = true;
                    }
                }
                Operator op = {token.type, is_unary};
                //check bad input
                if (!is_unary && (operand_stack.empty() || (i > 0 && tokens[i - 1].type == TokenType::LeftParen))) {
                    throw runtime_error("Invalid syntax: Operator without operands");
                }
                //apply precidence rules
                while (!operator_stack.empty() && get_operator_priority(operator_stack.back()) >= get_operator_priority(op)) {
                    if (operator_stack.back().type == TokenType::LeftParen) break;
                    combine_nodes(operand_stack, operator_stack);
                }
                operator_stack.push_back(op);
                break;
            }
            default:
                throw runtime_error("Syntax");
        }
    }
    //check if invalid parenthesis, if not combine nodes
    while (!operator_stack.empty()) {
        if (operator_stack.back().type == TokenType::LeftParen) {
            throw runtime_error("Syntax: Invalid Parentheses");
        }
        combine_nodes(operand_stack, operator_stack);
    }
    //check if stack is empty
    if (operand_stack.size() != 1) {
        throw runtime_error("Syntax");
    }
    //return the last element on the stack
    //it should be a single node - the root of the AST
    return operand_stack.back();
}

void test_parses_basic_expression() {
    //test parsing 11 + 2
    vector<Token> nodes = {
        {TokenType::Number, 11},
        {TokenType::Plus, 0},
        {TokenType::Number, 2}
    };
    ASTNode result = parse(nodes);
    assert(holds_alternative<shared_ptr<BinaryNode>>(result));
    auto binary_node = get<shared_ptr<BinaryNode>>(result);
    assert(binary_node->priority == get_binary_operator(TokenType::Plus).first);
    assert(binary_node->op == BinaryOperator::Plus);
    assert(holds_alternative<shared_ptr<NumberNode>>(binary_node->left));
    auto left_node = get<shared_ptr<NumberNode>>(binary_node->left);
    assert(left_node->value == 11);
    assert(holds_alternative<shared_ptr<NumberNode>>(binary_node->right));
    auto right_node = get<shared_ptr<NumberNode>>(binary_node->right);
    assert(right_node->value == 2);
}

void test_parses_expression_with_precedence() {
    //test parsing 3 + 4 * 2
    vector<Token> nodes = {
        {TokenType::Number, 3},
        {TokenType::Plus, 0},
        {TokenType::Number, 4},
        {TokenType::Multiply, 0},
        {TokenType::Number, 2}
    };
    ASTNode result = parse(nodes);
    assert(holds_alternative<shared_ptr<BinaryNode>>(result));
    auto binary_node = get<shared_ptr<BinaryNode>>(result);
    assert(binary_node->priority == get_binary_operator(TokenType::Plus).first);
    assert(binary_node->op == BinaryOperator::Plus);
    assert(holds_alternative<shared_ptr<NumberNode>>(binary_node->left));
    auto left_node = get<shared_ptr<NumberNode>>(binary_node->left);
    assert(left_node->value == 3);
    assert(holds_alternative<shared_ptr<BinaryNode>>(binary_node->right));
    auto right_node = get<shared_ptr<BinaryNode>>(binary_node->right);
    assert(right_node->priority == get_binary_operator(TokenType::Multiply).first);
    assert(right_node->op == BinaryOperator::Multiply);
    assert(holds_alternative<shared_ptr<NumberNode>>(right_node->left));
    auto multiply_left = get<shared_ptr<NumberNode>>(right_node->left);
    assert(multiply_left->value == 4);
    assert(holds_alternative<shared_ptr<NumberNode>>(right_node->right));
    auto multiply_right = get<shared_ptr<NumberNode>>(right_node->right);
    assert(multiply_right->value == 2);
}

void test_parses_expression_with_exponentiation() {
    //test parsing 2 ** 3 * 4
    vector<Token> nodes = {
        {TokenType::Number, 2},
        {TokenType::Exponent, 0},
        {TokenType::Number, 3},
        {TokenType::Multiply, 0},
        {TokenType::Number, 4}
    };
    ASTNode result = parse(nodes);
    assert(holds_alternative<shared_ptr<BinaryNode>>(result));
    auto binary_node = get<shared_ptr<BinaryNode>>(result);
    assert(binary_node->priority == get_binary_operator(TokenType::Multiply).first);
    assert(binary_node->op == BinaryOperator::Multiply);
    assert(holds_alternative<shared_ptr<BinaryNode>>(binary_node->left));
    auto exp_node = get<shared_ptr<BinaryNode>>(binary_node->left);
    assert(exp_node->priority == get_binary_operator(TokenType::Exponent).first);
    assert(exp_node->op == BinaryOperator::Exponent);
    assert(holds_alternative<shared_ptr<NumberNode>>(exp_node->left));
    auto base_node = get<shared_ptr<NumberNode>>(exp_node->left);
    assert(base_node->value == 2);
    assert(holds_alternative<shared_ptr<NumberNode>>(exp_node->right));
    auto exponent_node = get<shared_ptr<NumberNode>>(exp_node->right);
    assert(exponent_node->value == 3);
    assert(holds_alternative<shared_ptr<NumberNode>>(binary_node->right));
    auto right_node = get<shared_ptr<NumberNode>>(binary_node->right);
    assert(right_node->value == 4);
}

void test_parses_expression_with_parentheses() {
    //test parsing (3 + 4) * 2
    vector<Token> tokens = {
        {TokenType::LeftParen, 0},
        {TokenType::Number, 3},
        {TokenType::Plus, 0},
        {TokenType::Number, 4},
        {TokenType::RightParen, 0},
        {TokenType::Multiply, 0},
        {TokenType::Number, 2}
    };
    ASTNode result = parse(tokens);
    assert(holds_alternative<shared_ptr<BinaryNode>>(result));
    auto multiply_node = get<shared_ptr<BinaryNode>>(result);
    assert(multiply_node->priority == get_binary_operator(TokenType::Multiply).first);
    assert(multiply_node->op == BinaryOperator::Multiply);
    assert(holds_alternative<shared_ptr<BinaryNode>>(multiply_node->left));
    auto add_node = get<shared_ptr<BinaryNode>>(multiply_node->left);
    assert(add_node->priority == get_binary_operator(TokenType::Plus).first);
    assert(add_node->op == BinaryOperator::Plus);
    assert(holds_alternative<shared_ptr<NumberNode>>(add_node->left));
    assert(holds_alternative<shared_ptr<NumberNode>>(add_node->right));
    assert(get<shared_ptr<NumberNode>>(add_node->left)->value == 3);
    assert(get<shared_ptr<NumberNode>>(add_node->right)->value == 4);
    assert(holds_alternative<shared_ptr<NumberNode>>(multiply_node->right));
    assert(get<shared_ptr<NumberNode>>(multiply_node->right)->value == 2);
}

void test_parses_negative_number() {
    //test parsing -2
    vector<Token> tokens = {
        {TokenType::Minus, 0},
        {TokenType::Number, 2}
    };
    ASTNode result = parse(tokens);
    assert(holds_alternative<shared_ptr<UnaryNode>>(result));
    auto unary_node = get<shared_ptr<UnaryNode>>(result);
    assert(unary_node->op == UnaryOperator::Negate);
    assert(holds_alternative<shared_ptr<NumberNode>>(unary_node->child));
    auto number_node = get<shared_ptr<NumberNode>>(unary_node->child);
    assert(number_node->value == 2);
}

void test_parses_expression_with_modulo() {
    //test parsing 10 % 3
    vector<Token> tokens = {
        {TokenType::Number, 10},
        {TokenType::Modulo, 0},
        {TokenType::Number, 3}
    };
    ASTNode result = parse(tokens);
    assert(holds_alternative<shared_ptr<BinaryNode>>(result));
    auto binary_node = get<shared_ptr<BinaryNode>>(result);
    assert(binary_node->op == BinaryOperator::Modulo);
    assert(holds_alternative<shared_ptr<NumberNode>>(binary_node->left));
    auto left_node = get<shared_ptr<NumberNode>>(binary_node->left);
    assert(left_node->value == 10);
    assert(holds_alternative<shared_ptr<NumberNode>>(binary_node->right));
    auto right_node = get<shared_ptr<NumberNode>>(binary_node->right);
    assert(right_node->value == 3);
}

void test_parses_expression_with_negative_number() {
    //test parsing 5 + -3
    vector<Token> tokens = {
        {TokenType::Number, 5},
        {TokenType::Plus, 0},
        {TokenType::Minus, 0},
        {TokenType::Number, 3}
    };
    ASTNode result = parse(tokens);
    assert(holds_alternative<shared_ptr<BinaryNode>>(result));
    auto binary_node = get<shared_ptr<BinaryNode>>(result);
    assert(binary_node->op == BinaryOperator::Plus);
    assert(holds_alternative<shared_ptr<NumberNode>>(binary_node->left));
    auto left_node = get<shared_ptr<NumberNode>>(binary_node->left);
    assert(left_node->value == 5);
    assert(holds_alternative<shared_ptr<UnaryNode>>(binary_node->right));
    auto unary_node = get<shared_ptr<UnaryNode>>(binary_node->right);
    assert(unary_node->op == UnaryOperator::Negate);
    assert(holds_alternative<shared_ptr<NumberNode>>(unary_node->child));
    auto number_node = get<shared_ptr<NumberNode>>(unary_node->child);
    assert(number_node->value == 3);
}

void test_parses_expression_with_unary_minus() {
    //test parsing 3 * -2
    vector<Token> tokens = {
        {TokenType::Number, 3},
        {TokenType::Multiply, 0},
        {TokenType::Minus, 0},
        {TokenType::Number, 2}
    };
    ASTNode result = parse(tokens);
    assert(holds_alternative<shared_ptr<BinaryNode>>(result));
    auto multiply_node = get<shared_ptr<BinaryNode>>(result);
    assert(multiply_node->op == BinaryOperator::Multiply);
    assert(holds_alternative<shared_ptr<NumberNode>>(multiply_node->left));
    auto left_node = get<shared_ptr<NumberNode>>(multiply_node->left);
    assert(left_node->value == 3);
    assert(holds_alternative<shared_ptr<UnaryNode>>(multiply_node->right));
    auto unary_node = get<shared_ptr<UnaryNode>>(multiply_node->right);
    assert(unary_node->op == UnaryOperator::Negate);
    assert(holds_alternative<shared_ptr<NumberNode>>(unary_node->child));
    auto number_node = get<shared_ptr<NumberNode>>(unary_node->child);
    assert(number_node->value == 2);
}

void test_invalid_expression_star_minus_two() {
    //test parsing * - 2 expecting caught exception
    vector<Token> tokens = {
        {TokenType::Multiply, 0},
        {TokenType::Minus, 0},
        {TokenType::Number, 2}
    };
    try {
        ASTNode result = parse(tokens);
        assert(false);
    } catch (const exception& e) {}
}
 
//run all parser tests
void test_parser() {
    test_parses_basic_expression();
    test_parses_expression_with_precedence();
    test_parses_expression_with_exponentiation();
    test_parses_expression_with_parentheses();
    test_parses_negative_number();
    test_parses_expression_with_negative_number();
    test_parses_expression_with_unary_minus();
    test_invalid_expression_star_minus_two();
    test_parses_expression_with_modulo();
}

#endif
