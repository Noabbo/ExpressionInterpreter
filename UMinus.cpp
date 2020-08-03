//
// Created by noa on 19/11/2019.
//

#include "UMinus.h"
// constructor
UMinus::UMinus(Expression *e) : UnaryOperator(e){}

// getter
Expression* UMinus::getEx() {
    return this->ex;
}

// calculate
double UMinus::calculate() {
    return (this->ex->calculate()) * (-1);
}
// destructor
UMinus::~UMinus() {
    delete(this->ex);
}