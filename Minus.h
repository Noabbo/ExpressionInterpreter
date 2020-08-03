//
// Created by noa on 19/11/2019.
//

#ifndef UNTITLED_MINUS_H
#define UNTITLED_MINUS_H

#include "BinaryOperator.h"
class Minus : public BinaryOperator {
public:
    Minus(Expression *l, Expression *r);
    Expression* getLeft();
    Expression* getRight();
    double calculate();
    virtual ~Minus();
};


#endif //UNTITLED_MINUS_H
