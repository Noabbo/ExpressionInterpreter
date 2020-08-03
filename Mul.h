//
// Created by noa on 19/11/2019.
//

#ifndef UNTITLED_MUL_H
#define UNTITLED_MUL_H

#include "BinaryOperator.h"
class Mul : public BinaryOperator {
public:
    Mul(Expression *l, Expression *r);
    Expression* getLeft();
    Expression* getRight();
    double calculate();
    virtual ~Mul();
};


#endif //UNTITLED_MUL_H
