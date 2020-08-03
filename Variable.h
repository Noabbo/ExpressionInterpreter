//
// Created by noa on 19/11/2019.
//

#ifndef EX1_VARIABLE_H
#define EX1_VARIABLE_H

#include <string.h>
#include "Expression.h"
class Variable : public Expression {
    string name;
    double value;
public:
    Variable(string n, double v);
    double calculate();
    Variable& operator+=(const double v) const;
    Variable& operator-=(const double v) const;
    Variable& operator++() const;
    Variable& operator--() const;
    Variable& operator++(const int v) const;
    Variable& operator--(const int v) const;
    virtual ~Variable();
};


#endif //EX1_VARIABLE_H
