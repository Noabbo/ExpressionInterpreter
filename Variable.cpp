//
// Created by noa on 19/11/2019.
//

#include <string>
#include "Variable.h"

// constructor
Variable::Variable(string n, double v) {
    this->name.insert(0, n);
    this->value = v;
}

// calculate
double Variable::calculate() {
    return this->value;
}

//operators
Variable& Variable::operator+=(const double v) const {
    Variable *newVar = new Variable(this->name, this->value + v);
    return *newVar;
}
Variable& Variable::operator-=(const double v) const {
    Variable *newVar = new Variable(this->name, this->value - v);
    return *newVar;
}
Variable& Variable::operator++() const {
    Variable *newVar = new Variable(this->name, this->value + 1);
    return *newVar;
}
Variable& Variable::operator--() const {
    Variable *newVar = new Variable(this->name, this->value - 1);
    return *newVar;
}
Variable& Variable::operator++(const int) const {
    Variable *newVar = new Variable(this->name, this->value + 1);
    return *newVar;
}
Variable& Variable::operator--(const int) const {
    Variable *newVar = new Variable(this->name, this->value - 1);
    return *newVar;
}

// destructor
Variable:: ~Variable() {}