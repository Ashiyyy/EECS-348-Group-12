#ifndef EVALUATOR_CPP
#define EVALUATOR_CPP

#include <variant>
#include <memory>
#include <stdexcept>
#include <cmath>
#include "parser.h"

using namespace std;

float evaluate(const ASTNode& node) {
    //if the node is a number, return it!
    if (holds_alternative<shared_ptr<NumberNode>>(node)) {
        return get<shared_ptr<NumberNode>>(node)->value;
    //if the node is a binary node
    } else if (holds_alternative<shared_ptr<BinaryNode>>(node)) {
        auto binary_node = get<shared_ptr<BinaryNode>>(node);
        //recursively evaluate left and right children
        float left_value = evaluate(binary_node->left);
        float right_value = evaluate(binary_node->right);
        //perform the operation
        switch (binary_node->op) {
            case BinaryOperator::Modulo:
                if (right_value == 0) {
                    throw runtime_error("Invalid Modulo by zero");
                }
                return (int)left_value % (int)right_value;
            case BinaryOperator::Plus:
                return left_value + right_value;
            case BinaryOperator::Minus:
                return left_value - right_value;
            case BinaryOperator::Multiply:
                return left_value * right_value;
            case BinaryOperator::Divide:
                //catch division by zero
                if (right_value == 0) {
                    throw runtime_error("Division by zero");
                }
                return left_value / right_value;
            case BinaryOperator::Exponent:
                return pow(left_value, right_value);
            default:
                //throw an error if the operator is unknown
                throw runtime_error("In evaluation");
        }
    //if node is unary
    } else if (holds_alternative<shared_ptr<UnaryNode>>(node)) {
        auto unary_node = get<shared_ptr<UnaryNode>>(node);
        //recursively evaluate the child
        float child_value = evaluate(unary_node->child);
        //perform the operation
        switch (unary_node->op) {
            case UnaryOperator::Negate:
                return -child_value;
            case UnaryOperator::Parenthesis:
                return child_value;
            default:
                //throw an error if the operator is unknown
                throw runtime_error("In evaluation");
        }
    }
    else {
        //throw an error if the node is unknown
        throw runtime_error("In evaluation");
    }
}

#endif
