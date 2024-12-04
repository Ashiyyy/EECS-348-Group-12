#ifndef PARSER_H
#define PARSER_H

#include <variant>
#include <memory>
#include <vector>
#include <stdexcept>
#include <cassert>
#include <iostream>
#include "tokenizer.h"

//declare classes that hold data
class BinaryNode;
class UnaryNode;
class NumberNode;

//define ast node
using ASTNode = variant<shared_ptr<BinaryNode>, shared_ptr<UnaryNode>, shared_ptr<NumberNode>>;

//define binary and unary operators
enum BinaryOperator {Plus, Minus, Multiply, Divide, Exponent, Modulo};
enum UnaryOperator {Negate, Parenthesis};

/*define binary node:
    - priority: the priority of the operator
    - op: the operator
    - left: the left operand
    - right: the right operand

*/  
class BinaryNode {
public:
    int priority;
    BinaryOperator op;
    ASTNode left;
    ASTNode right;
    BinaryNode(int p, ASTNode l, ASTNode r, BinaryOperator o) : priority(p), left(l), right(r), op(o) {}
};

/*define unary node:
    - priority: the priority of the operator
    - op: the operator
    - child: the child node
*/
class UnaryNode {
public:
    int priority;
    UnaryOperator op;
    ASTNode child;
    UnaryNode(int p, ASTNode c, UnaryOperator o) : priority(p), child(c) , op(o) {}
};

/*define number node:
    - value: the value of the number
*/
class NumberNode {
public:
    float value;
    NumberNode(float v) : value(v) {}
};

//parse function declaration
ASTNode parse(const vector<Token>& nodes);
//parse test function declarations
void test_parser();

#endif