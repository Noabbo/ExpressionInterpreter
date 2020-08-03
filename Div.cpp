//
// Created by noa on 19/11/2019.
//
#include <stdexcept>
#include "Div.h"

Div::Div(Expression *l, Expression *r) : BinaryOperator(l, r) {}

// getters
Expression* Div::getLeft() {
    return this->left;
}
Expression* Div::getRight() {
    return this->right;
}

// calculate
double Div::calculate() {
    // throw exception of dividing by 0
   if (this->right->calculate() == 0) {
       throw ("attempt to divide by 0!");
    }
    return (this->left->calculate()) / (this->right->calculate());
}
// destructor
Div::~Div() {
    delete(this->left);
    delete(this->right);
}