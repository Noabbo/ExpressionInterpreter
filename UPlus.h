//
// Created by noa on 19/11/2019.
//

#ifndef UNTITLED_UPLUS_H
#define UNTITLED_UPLUS_H

#include "UnaryOperator.h"
class UPlus : public UnaryOperator {
public:
    UPlus(Expression *e);
    Expression* getEx();
    double calculate();
    virtual ~UPlus();
};


#endif //UNTITLED_UPLUS_H
