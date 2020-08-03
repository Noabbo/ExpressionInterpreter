//
// Created by noa on 19/11/2019.
//

#ifndef UNTITLED_VALUE_H
#define UNTITLED_VALUE_H


#include "Expression.h"

class Value : public Expression {
    double value;
public:
    Value(double v);
    double calculate();
    virtual ~Value() {}
};


#endif //UNTITLED_VALUE_H
