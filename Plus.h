//
// Created by noa on 19/11/2019.
//

#ifndef UNTITLED_PLUS_H
#define UNTITLED_PLUS_H

#include "BinaryOperator.h"
class Plus : public BinaryOperator {
public:
    Plus(Expression *l, Expression *r);
    Expression* getLeft();
    Expression* getRight();
    double calculate();
    virtual ~Plus();
};


#endif //UNTITLED_PLUS_H
