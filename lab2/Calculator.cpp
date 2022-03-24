//
// Created by makmn on 3/23/2022.
//

#include "Calculator.h"
#include <iostream>
#include <math.h>
using namespace std;


void Calculator::calculate(stack<double> &operandStack, stack<char> &operatorStack) {
    char mathOperator = operatorStack.top();
    operatorStack.pop();

    double calculatedValue;

    double secondValue = operandStack.top();
    operandStack.pop();
    double firstValue = operandStack.top();
    operandStack.pop();

    switch(mathOperator) {
        case PLUS:
            calculatedValue = firstValue + secondValue;
            break;
        case MINUS:
            calculatedValue = firstValue - secondValue;
            break;
        case MULTIPLY:
            calculatedValue = firstValue * secondValue;
            break;
        case DIVIDE:
            calculatedValue = firstValue / secondValue;
            break;
        case EXPONENT:
            calculatedValue = pow(firstValue, secondValue);
            break;
        default:
            cout << "Oh no! An error has occurred! What have you done?! ;_;" << endl;
    }
    operandStack.push(calculatedValue);
}

double Calculator::infixToPostfix(string givenExpression) {
    int pfx = 0;
    char stackTracker = 0;

    stack<double> operandStack;
    stack<char> operatorStack;

    while (pfx < givenExpression.size()) {

        if (isdigit(givenExpression[pfx])) {
            // convert character number to an actual number
            double number = givenExpression[pfx] - '0';
            operandStack.push(number);
        }
        else {
            switch (givenExpression[pfx]) {

                // check if the current character is an exponent
                case EXPONENT:
                    // if no exponent on the stack, push it on the stack
                    if (operatorStack.empty() || operatorStack.top() != EXPONENT) {
                        operatorStack.push(givenExpression[pfx]);
                    }
                        // if there is an exponent on the stack, that means we need to apply the operation on the last two numbers
                    else if (operatorStack.top() == EXPONENT) {
                        calculate(operandStack, operatorStack);
                        continue; // we continue while staying at the '^' symbol since there may be another '^' on top
                    }
                    break;

                    // check if the current character is a multiplication or division symbol
                case MULTIPLY:
                case DIVIDE:
                    // if the top of the stack is '+', '-', '(', or the stack is empty, then we push it onto the stack
                    if (operatorStack.empty() || operatorStack.top() == PLUS || operatorStack.top()  == MINUS || operatorStack.top()  == OPENPAREN) {
                        operatorStack.push(givenExpression[pfx]);
                    }
                        // if the current symbol on the stack is a '^', '*', or '/', then we are going to calculate from the top operator
                    else if (operatorStack.top() == EXPONENT || operatorStack.top()  == MULTIPLY || operatorStack.top()  == DIVIDE) {
                        calculate(operandStack, operatorStack);
                        continue;
                    }
                    break;

                    // check if the current character is an addition or subtraction symbol
                case PLUS:
                case MINUS:
                    // if the current symbol on the stack is either an open parentheses or if the stack is empty, push the symbol
                    if (operatorStack.empty() || operatorStack.top() == OPENPAREN) {
                        operatorStack.push(givenExpression[pfx]);
                    }
                        // if the current symbol on the stack is not an open parentheses and the stack is not empty, calculate from the top operator
                    else {
                        calculate(operandStack, operatorStack);
                        continue;
                    }
                    break;

                    // check if the current character is an open parentheses
                case OPENPAREN:
                    operatorStack.push(givenExpression[pfx]);
                    break;

                    // check if the current character is a close parentheses
                case CLOSEPAREN:

                    stackTracker = operatorStack.top(); // don't pop, we only want to check
                    while (stackTracker != '(') {

                        calculate(operandStack, operatorStack);
                        stackTracker = operatorStack.top();
                    }
                    operatorStack.pop(); // pop the open parentheses
                    stackTracker = 0;
                    break;
            }
        }
        // finally, increment the index count
        pfx++;
        // end the while loop once the index count goes out of bounds
        if (pfx == givenExpression.size()) {
            // pop the stack onto the postfix expression
            while (operatorStack.size() != 0) {
                calculate(operandStack, operatorStack);
            }
        }
    }
    double answer = operandStack.top(); // get the answer from the top of the stack
    return answer;
};
