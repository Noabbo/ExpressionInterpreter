//
// Created by noa on 19/11/2019.
//

#include "Plus.h"
// constructor
Plus::Plus(Expression *l, Expression *r) : BinaryOperator(l, r) {}

// getters
Expression* Plus::getLeft() {
    return this->left;
}
Expression* Plus::getRight() {
    return this->right;
}

// calculate
double Plus::calculate() {
    return (this->left->calculate()) + (this->right->calculate());
}
// destructor
Plus::~Plus() {
    delete(this->left);
    delete(this->right);
}