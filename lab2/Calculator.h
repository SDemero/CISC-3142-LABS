//
// Created by makmn on 3/23/2022.
//


#ifndef CISC_3142_LAB_2_CALCULATOR_H
#define CISC_3142_LAB_2_CALCULATOR_H
#include <string>
#include <stack>
using namespace std;

struct Calculator {

    // list of valid operators to use with this calculator
    enum operators { PLUS = '+', MINUS = '-', MULTIPLY = '*', DIVIDE = '/', EXPONENT = '^', OPENPAREN = '(', CLOSEPAREN = ')' };

    // function to calculate a binary expression
    void calculate(stack<double> &operandStack, stack<char> &operatorStack);

    // function to convert infix to postfix (uses calculate as a helper function)
    double infixToPostfix(string givenExpression);

};
#endif //CISC_3142_LAB_2_CALCULATOR_H

