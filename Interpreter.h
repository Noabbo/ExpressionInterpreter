//
// Created by noa on 24/11/2019.
//

#ifndef UNTITLED_INTERPRETER_H
#define UNTITLED_INTERPRETER_H

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <list>
#include <unordered_map>
#include <queue>
#include "Expression.h"
#include "Value.h"
#include "Variable.h"
#include "UnaryOperator.h"
#include "UPlus.h"
#include "UMinus.h"
#include "BinaryOperator.h"
#include "Plus.h"
#include "Minus.h"
#include "Mul.h"
#include "Div.h"
class Interpreter {
    unordered_map<string, double> variables;
public:
    Expression* interpret(string equation);
    bool isOpMorePrecedent(char op, string check);
    bool isStringValid(string equation);
    bool hasNoBrackets(string equation);
    string findVarOrNum(string equation, int pos);
    bool isVarValid(string var);
    bool isNumValid(string num);
    void setVariables(string vars);
};


#endif //UNTITLED_INTERPRETER_H
