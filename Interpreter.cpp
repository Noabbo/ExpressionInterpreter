//
// Created by noa on 24/11/2019.
//

#include "Interpreter.h"
Expression* Interpreter::interpret(string equation) {
    Expression *final;
    list <string> stack;
    list <Expression*> finalStack;
    queue <string> tokens;
    string name;
    // expression is valid
    if (isStringValid(equation)) {
        for (unsigned int i = 0; i < equation.length(); i++) {
            // number
            if ((equation[i] > 47) && (equation[i] < 58)) {
                string num = findVarOrNum(equation, i);
                tokens.push(num);
                i += num.length() - 1;
            } else if (((equation[i] > 96) && (equation[i] < 123)) ||
                       ((equation[i] > 64) && (equation[i] < 91))) {
                string var = findVarOrNum(equation, i);
                tokens.push(var);
                i += var.length() - 1;
            } else {
                // UMinus or UPlus
                if (((equation[i] == '-') || (equation[i] == '+')) && ((((equation[i+1] > 47) && (equation[i+1] < 58))
                                                                        && (((equation[i-1] == '(')) || (i == 0))) ||
                                                                       ((equation[i+1] == '(') && ((i == 0) || (equation[i-1] == '('))))) {
                    string s;
                    if (equation[i] == '-') {
                        s.push_back('-');
                        s.push_back('-');
                    } else {
                        s.push_back('+');
                        s.push_back('+');
                    }
                    stack.push_back(s);
                } else {
                    // operator or bracket
                    if (stack.empty()) {
                        string s(1, equation[i]);
                        stack.push_back(s);
                    } else {
                        while (!stack.empty()) {
                            if (equation[i] == ')') {
                                while (stack.back().compare("(") != 0) {
                                    // add operand to queue
                                    tokens.push(stack.back());
                                    // pop operand from stack
                                    stack.pop_back();
                                }
                                // pop opening bracket
                                stack.pop_back();
                                break;
                            } else if (isOpMorePrecedent(equation[i], stack.back())) {
                                string s(1, equation[i]);
                                stack.push_back(s);
                                break;
                            } else {
                                // add operand to queue
                                tokens.push(stack.back());
                                // pop operand from stack
                                stack.pop_back();
                            }
                        }
                    }
                }
            }
        }
        // pop all operands to the queue
        while (!stack.empty()) {
            // add operand to queue
            tokens.push(stack.back());
            // pop operand from stack
            stack.pop_back();
        }
        // creating expression
        while (!tokens.empty()) {
            //e = nullptr;
            // token is a number
            if ((tokens.front().front() > 47) && (tokens.front().front() < 58)) {
                Expression *e = new Value(stod(tokens.front()));
                finalStack.push_back(e);
                tokens.pop();
                // token is a variable
            } else if (((tokens.front().front() > 96) && (tokens.front().front() < 123)) ||
                       ((tokens.front().front() > 64) && (tokens.front().front() < 91))){
                double value = variables.at(tokens.front());
                // create char *name for variable
                if (!name.empty()) {
                    name.clear();
                }
                name.insert(0, tokens.front());
                Expression *e = new Variable(name, value);
                //free(name);
                finalStack.push_back(e);
                tokens.pop();
                // token is an operand
            } else {
                Expression *e;
                if ((tokens.front().compare("--") == 0) || (tokens.front().compare("++") == 0)) {
                    string operand = tokens.front();
                    tokens.pop();
                    // extracting the right expression
                    Expression *exp = finalStack.back();
                    finalStack.pop_back();
                    if (operand.compare("--") == 0) {
                       e = new UMinus(exp);
                    } else {
                        e = new UPlus(exp);
                    }
                } else {
                    // extracting the operator
                    char operand = tokens.front()[0];
                    tokens.pop();
                    // extracting the right expression
                    Expression *right = finalStack.back();
                    finalStack.pop_back();
                    // extracting the left expression
                    Expression *left = finalStack.back();
                    finalStack.pop_back();

                    switch (operand) {
                        case '+':
                            e = new Plus(left, right);
                            break;
                        case '-':
                            e = new Minus(left, right);
                            break;
                        case '*':
                            e = new Mul(left, right);
                            break;
                        case '/':
                            e = new Div(left, right);
                            break;
                    }
                }
                // adding expression to stack
                finalStack.push_back(e);
            }
        }
        final = finalStack.back();
    }
    return final;
}

bool Interpreter::isOpMorePrecedent(char op, string check) {
    if ((op == '(') || (op == ')') || (check.compare("(") == 0) || (check.compare(")") == 0)) {
        return true;
    }
    if ((check.compare("--") == 0) || (check.compare("++") == 0)) {
        return false;
    }
    switch(op) {
        case '*':
            if ((check.compare("+") != 0) && (check.compare("-") != 0)) {
                return false;
            }
            break;
        case '/':
            if ((check.compare("+") != 0) && (check.compare("-") != 0)) {
                return false;
            }
            break;
        case '+':
            return false;
        case '-':
            return false;
        default:
            break;
    }
    return true;
}

bool Interpreter::isStringValid(string equation) {
    unsigned int i = 0;
    // no brackets - simple expression
    if (hasNoBrackets(equation)) {
        string var;
        while (i != equation.length()) {
            // starts with letter - variable
            if (((equation[i] > 96) && (equation[i] < 123)) ||
                ((equation[i] > 64) && (equation[i] < 91))) {
                var = findVarOrNum(equation, i);
                // string not found as variable in map
                if (!isVarValid(var)) {
                    throw ("variable doesn't exist or doesn't have value");
                }
            } else if ((equation[i] > 47) && (equation[i] < 58)) {
                // starts with number
                var = findVarOrNum(equation, i);
                if (!isNumValid(var)) {
                    throw ("invalid number");
                }
            } else if ((equation[i] == '+') || (equation[i] == '-') ||
                       (equation[i] == '*') || (equation[i] == '/')) {
                // consecutive operands
                throw ("syntax error - missing variable or value");
            }
            // move iterator past variable or number
            i += var.length();
            if (i != equation.length()) {
                if ((equation[i] != '+') && (equation[i] != '-') &&
                    (equation[i] != '*') && (equation[i] != '/')) {
                    // consecutive variables
                    throw ("syntax error - missing operand");
                } else {
                    i++;
                }
            }
        }
    } else {
        // starts with letter - variable
        if (((equation[0] > 96) && (equation[0] < 123)) ||
            ((equation[0] > 64) && (equation[0] < 91))) {
            string v = findVarOrNum(equation, i);
            // string not found as variable in map
            if (!isVarValid(v)) {
                throw ("variable doesn't exist or doesn't have value");
            }
            if ((equation[v.length()] != '+') && (equation[v.length()] != '-') &&
                (equation[v.length()] != '*') && (equation[v.length()] != '/')) {
                // consecutive variables
                throw ("syntax error - missing operand");
            }
            string part = equation.substr(v.length() + 1, string::npos);
            return isStringValid(part);
        } else if ((equation[0] > 47) && (equation[0] < 58)) {
            // starts with number
            string num = findVarOrNum(equation, i);
            if (!isNumValid(num)) {
                throw ("invalid number");
            }
            if ((equation[num.length()] != '+') && (equation[num.length()] != '-') &&
                (equation[num.length()] != '*') && (equation[num.length()] != '/') &&
                (equation[num.length()] != '(') && (equation[num.length()] != ')')) {
                // consecutive variables
                throw ("syntax error - missing operand");
            }
            string part = equation.substr(num.length() + 1, string::npos);
            return isStringValid(part);
        } else {
            switch (equation[0]) {
                case ')':
                    throw ("syntax error - misplaced closing bracket");
                    break;
                case '(': {
                    // end of expression or empty sub-expression
                    if (((unsigned)equation[1] == string::npos) || (equation[1] == ')')) {
                        throw ("syntax error - empty expression");
                    }
                    int closeBracket = equation.rfind(')', string::npos);
                    if ((unsigned)closeBracket == string::npos) {
                        throw ("syntax error - no closing bracket");
                    }
                    string part = equation.substr(1, closeBracket - 1);
                    if ((part[0] == '/') || (part[0] == '*')) {
                        throw ("syntax error - invalid operand");
                    }
                    return isStringValid(part);
                    break;
                }
                case '-':
                    // syntax error - no brackets before variable
                    if (((equation[1] > 96) && (equation[1] < 123)) ||
                        ((equation[1] > 64) && (equation[1] < 91))) {
                        throw ("syntax error - no brackets before UMinus of variable");
                    }
                    if ((equation[1] == '+') || (equation[1] == '-') ||
                        (equation[1] == '*') || (equation[1] == '/')) {
                        throw ("syntax error - two consecutive operands");
                    }
                    if (equation[1] == '(') {
                        string part = equation.substr(1, string::npos);
                        return isStringValid(part);
                    } else if ((equation[0] > 47) && (equation[0] < 58)) {
                        string num = findVarOrNum(equation, i);
                        if (!isNumValid(num)) {
                            throw ("invalid number");
                        }
                        if ((equation[num.length()] != '+') && (equation[num.length()] != '-') &&
                            (equation[num.length()] != '*') && (equation[num.length()] != '/')) {
                            // consecutive variables
                            throw ("syntax error - missing operand");
                        }
                        string part = equation.substr(num.length() + 1, string::npos);
                        return isStringValid(part);
                    }
                    break;
                case '+':
                    // syntax error - no brackets before variable
                    if (((equation[1] > 96) && (equation[1] < 123)) ||
                        ((equation[1] > 64) && (equation[1] < 91))) {
                        throw ("syntax error - no brackets before UPlus of variable");
                    }
                    if ((equation[1] == '+') || (equation[1] == '-') ||
                        (equation[1] == '*') || (equation[1] == '/')) {
                        throw ("syntax error - two consecutive operands");
                    }
                    if (equation[1] == '(') {
                        string part = equation.substr(1, string::npos);
                        return isStringValid(part);
                    } else if ((equation[0] > 47) && (equation[0] < 58)) {
                        string num = findVarOrNum(equation, i);
                        if (!isNumValid(num)) {
                            throw ("invalid number");
                        }
                        if ((equation[num.length()] != '+') && (equation[num.length()] != '-') &&
                            (equation[num.length()] != '*') && (equation[num.length()] != '/')) {
                            // consecutive variables
                            throw ("syntax error - missing operand");
                        }
                        string part = equation.substr(num.length() + 1, string::npos);
                        return isStringValid(part);
                    }
                    break;
                case '*':
                    if ((equation[1] == '+') || (equation[1] == '-') ||
                        (equation[1] == '*') || (equation[1] == '/')) {
                        throw ("syntax error - two consecutive operands");
                    }
                    break;
                case '/':
                    if ((equation[1] == '+') || (equation[1] == '-') ||
                        (equation[1] == '*') || (equation[1] == '/')) {
                        throw ("syntax error - two consecutive operands");
                    }
                    break;
                default:
                    throw ("syntax error - invalid character");
            }
        }
    }
    return true;
}

bool Interpreter::hasNoBrackets(string equation) {
    for (char i : equation) {
        if ((i == '(') || (i == ')')) {
            return false;
        }
    }
    return true;
}

string Interpreter::findVarOrNum(string equation, int pos) {
    int i = pos;
    string var;
    while ((i < equation.length()) && (equation[i] != '+') &&
        (equation[i] != '-') && (equation[i] != '*') && (equation[i] != '/') &&
            (equation[i] != '(') && (equation[i] != ')')) {
        var.push_back(equation[i]);
        i++;
    }
    return var;
}

bool Interpreter::isVarValid(string var) {
    return !(variables.find(var) == variables.end());
}

bool Interpreter::isNumValid(string num) {
    int dot = 0;
    for (char j : num) {
        if ((j == '.') && (dot > 0)) {
            return false;
        }
        if (((j < 48) || (j > 57)) && (j != '.')) {
            return false;
        }
        if (j == '.') {
            dot++;
        }
    }
    return true;
}

void Interpreter::setVariables(string vars) {
    while (!vars.empty()) {
        int place = vars.find(';');
        string equation;
        if (place == string::npos) {
            equation = vars.substr(0, vars.length());
        } else {
            equation = vars.substr(0, place);
        }
        int equal = equation.find('=');
        if (equal == string::npos) {
            throw ("invalid setting of variables");
        }
        // create pair to put in map of variables
        string var = equation.substr(0, equal);
        string num = equation.substr(equal + 1, equation.length());
        if (!isNumValid(num)) {
            throw ("invalid number");
        }
        double value = stod(num);
        variables[var] = value;
        // deleting variable from string
        vars.erase(0, place == -1 ? vars.length() : place + 1);
    }
}