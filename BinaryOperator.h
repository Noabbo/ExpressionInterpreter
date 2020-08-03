//
// Created by noa on 19/11/2019.
//

#ifndef UNTITLED_BINARYOPERATOR_H
#define UNTITLED_BINARYOPERATOR_H

#include "Expression.h"
class BinaryOperator : public Expression{
protected:
    Expression *left;
    Expression *right;
public:
    BinaryOperator(Expression *l, Expression *r);
    virtual Expression* getLeft() = 0;
    virtual Expression* getRight() = 0;
    virtual double calculate() = 0;
    virtual ~BinaryOperator() {}
};


#endif //UNTITLED_BINARYOPERATOR_H
