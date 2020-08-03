//
// Created by noa on 19/11/2019.
//

#ifndef UNTITLED_UNARYOPERATOR_H
#define UNTITLED_UNARYOPERATOR_H

#include "Expression.h"
class UnaryOperator : public Expression {
protected:
    Expression *ex;
public:
    UnaryOperator(Expression *e);
    virtual Expression* getEx() = 0;
    virtual double calculate() = 0;
    virtual ~UnaryOperator() {}
};


#endif //UNTITLED_UNARYOPERATOR_H
