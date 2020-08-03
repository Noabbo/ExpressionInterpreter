//
// Created by noa on 19/11/2019.
//

#ifndef UNTITLED_UMINUS_H
#define UNTITLED_UMINUS_H

#include "UnaryOperator.h"
class UMinus : public UnaryOperator {
public:
    UMinus(Expression *e);
    Expression* getEx();
    double calculate();
    virtual ~UMinus();
};


#endif //UNTITLED_UMINUS_H
