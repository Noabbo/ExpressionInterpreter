//
// Created by noa on 19/11/2019.
//

#include "UPlus.h"
// constructor
UPlus::UPlus(Expression *e) : UnaryOperator(e){}

// getter
Expression* UPlus::getEx() {
    return this->ex;
}

// calculate
double UPlus::calculate() {
    return this->ex->calculate();
}
// destructor
UPlus::~UPlus() {
    delete(this->ex);
}