<include my_class.h>

// Assumptions: No negative number in the beginning. No numbers greater than one digit.

enum operators { PLUS = '+', MINUS = '-', MULTIPLY = '*', DIVIDE = '/', EXPONENT = '^', OPENPAREN = '(', CLOSEPAREN = ')' };

void calculate(stack<double> &operandStack, stack<char> &operatorStack) {
    cout << "in calculate1" <<endl;
    char mathOperator = operatorStack.top();
    operatorStack.pop();
    double calculatedValue;

    double secondValue = operandStack.top();
    operatorStack.pop();
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
    }
    operandStack.push(calculatedValue);
}

double infixToPostfix(string givenExpression) {
    int pfx = 0;
    char stackTracker = 0;

    stack<double> operandStack;
    stack<char> operatorStack;

//    string pfxStack = "";
//    string pfxExpression = {};


    while (pfx < givenExpression.size()) {

        cout << "Top of Operand Stack: ";
        for (int i = 0; i < operandStack.size(); i++) {
            cout << operandStack.top();
        }
        cout << endl;

        cout << "Top of Operator Stack: ";
        for (int i = 0; i < operatorStack.size(); i++) {
            cout << operatorStack.top();
        }
        cout << endl;

        if (isdigit(givenExpression[pfx])) {
            cout << "Pushing digit" << endl;
            operandStack.push((double)givenExpression[pfx]);
        }
        else {
            switch (givenExpression[pfx]) {

                // check if the current character is an exponent
                case EXPONENT:
                    cout << "help2" << endl;
                    // if no exponent on the stack, push it on the stack
                    if (operatorStack.top() != EXPONENT) {
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
                    cout << "help3" << endl;
                    // if the current symbol on the stack is a '^', '*', or '/', then we are going to calculate from the top operator
                    if (operatorStack.top() == EXPONENT || operatorStack.top()  == MULTIPLY || operatorStack.top()  == DIVIDE) {
                        cout << "Calculate from multiply/divide" << endl;
                        calculate(operandStack, operatorStack);
                        continue;
                    }
                        // if it's instead '+', '-', '(', or the stack is empty, then we push it onto the stack
                    else if (operatorStack.top() == PLUS || operatorStack.top()  == MINUS || operatorStack.top()  == OPENPAREN || operatorStack.size() == 0) {
                        cout << "Pushing multiply/divide" << endl;
                        operatorStack.push(givenExpression[pfx]);
                    }
                    break;

                    // check if the current character is an addition or subtraction symbol
                case PLUS:
                case MINUS:
                    cout << "help4" << endl;
                    // if the current symbol on the stack is either an open parentheses or if the stack is empty, push the symbol
                    if (operatorStack.size() == 0 || operatorStack.top() == OPENPAREN) {
                        cout << "help4a" << endl;
                        operatorStack.push(givenExpression[pfx]);
                    }
                        // if the current symbol on the stack is not an open parentheses and the stack is not empty, calculate from the top operator
                    else if (operatorStack.top() != OPENPAREN && operatorStack.size() != 0) {
                        cout << "help4b" << endl;
                        calculate(operandStack, operatorStack);
                        continue;
                    }
                    break;

                    // check if the current character is an open parentheses
                case OPENPAREN:
                    cout << "help5" << endl;
                    operatorStack.push(givenExpression[pfx]);
                    break;

                    // check if the current character is a close parentheses
                case CLOSEPAREN:
                    cout << "help6" << endl;
                    stackTracker = operatorStack.top(); // don't pop, we only want to check
                    while (stackTracker != '(') {
                        calculate(operandStack, operatorStack);
                        stackTracker = operatorStack.top();
                    }
                    stackTracker = 0;
                    break;
            }
        }
        // finally, increment the index count
        pfx++;
        // end the while loop once the index count goes out of bounds
        if (pfx == givenExpression.size()) {
            cout << "help7" << endl;
            // pop the stack onto the postfix expression
            while (operatorStack.size() != 0) {
                calculate(operandStack, operatorStack);
            }
        }
    }
    double answer = operandStack.top();
    std::cout << "Postfix Expression is: " << answer <<  std::endl;
    return answer;
};

std::string removeWhiteSpace(std::string givenExpression) {
    size_t pos = std::string::npos;

    while ((pos = givenExpression.find(" ")) != std::string::npos) {
        givenExpression.erase(pos, 1);
    }

    return givenExpression;

};

int main() {
    std::string testCase0 = "4 + 58 / 4"; // should be 6
    std::string testCase1 = "7 / 2 - 6 * (9 + 8 ^ 2) - 3"; // should be 6
    testCase1 = removeWhiteSpace(testCase0);
    std::cout << testCase1 << std::endl;

    infixToPostfix(testCase0);

    return 0;
}
