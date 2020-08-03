//
// Created by noa on 19/11/2019.
//

#include "Mul.h"
// constructor
Mul::Mul(Expression *l, Expression *r) : BinaryOperator(l, r) {}

// getters
Expression* Mul::getLeft() {
    return this->left;
}
Expression* Mul::getRight() {
    return this->right;
}

// calculate
double Mul::calculate() {
    return (this->left->calculate()) * (this->right->calculate());
}
// destructor
Mul::~Mul() {
    delete(this->left);
    delete(this->right);
}