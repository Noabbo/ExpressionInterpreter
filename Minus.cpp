//
// Created by noa on 19/11/2019.
//

#include "Minus.h"
// constructor
Minus::Minus(Expression *l, Expression *r) : BinaryOperator(l, r) {}

// getters
Expression* Minus::getLeft() {
    return this->left;
}
Expression* Minus::getRight() {
    return this->right;
}

// calculate
double Minus::calculate() {
    return (this->left->calculate()) - (this->right->calculate());
}
// destructor
Minus::~Minus() {
    delete(this->left);
    delete(this->right);
}