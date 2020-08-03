//
// Created by noa on 19/11/2019.
//

#ifndef UNTITLED_DIV_H
#define UNTITLED_DIV_H

#include "BinaryOperator.h"
class Div : public BinaryOperator {
public:
    Div(Expression *l, Expression *r);
    Expression* getLeft();
    Expression* getRight();
    double calculate();
    virtual ~Div();
};


#endif //UNTITLED_DIV_H
