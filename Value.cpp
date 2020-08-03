//
// Created by noa on 19/11/2019.
//

#include "Value.h"

// constructor
Value::Value(double v) {
    this->value = v;
}

// calculate
double Value::calculate() {
    return this->value;
}