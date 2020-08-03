//
// Created by noa on 19/11/2019.
//
#include "BinaryOperator.h"
// constructor
BinaryOperator::BinaryOperator(Expression *l, Expression *r) {
    this->left = l;
    this->right = r;
}