#include "Calculator.h"
#include <stdio.h>
#include <iostream>
using namespace std;

// Assumptions: No negative number in the beginning. No numbers greater than one digit.

struct Calculator;

string removeWhiteSpace(string givenExpression) {
    size_t pos = string::npos;

    while ((pos = givenExpression.find(" ")) != std::string::npos) {
        givenExpression.erase(pos, 1);
    }

    return givenExpression;

};

int main() {
//    std::string testCase0 = "4 + 8 / 4"; // should be 18.5 passes
//    std::string testCase1 = "7 / 2 - 6 * (9 + 8 ^ 2) - 3"; // should be -437.5 passes
//    std::string testCase2 = "5^2^3"; // should be 390625 fails

    // bring to life a calculator
    Calculator unreliableCalculator;
    string userInput;
    string userResponse;
    double answer;

    cout << "Welcome to The Poor Man's Calculator!" << endl;
    cout << "This calculator can calculate many mathematical expressions. The valid operators are: " << endl;
    cout << "The symbols:\n'+' for addition.\n'-' for subtraction,\n'*' for multiplication,\n'/' for division,\n'^' for exponentiation" << endl;
    cout << "You can also use parentheses to wrap different parts of your expression." << endl;
    cout << "Try it out!" << endl;

    while(true) {

        cout << "Enter an expression: ";

        // get user input
        getline(cin, userInput);
        // parsing area (currently only removing whitespace)
        userInput = removeWhiteSpace(userInput);

        // use the calculator to calculate the parsed expression
        answer = unreliableCalculator.infixToPostfix(userInput);

        cout << "We do some parsing on your input. Your parsed expression is: " << userInput << std::endl;
        cout << "The answer to this expression is " << answer << endl;
        cout << "Would you like to calculate another expression? Enter yes or no." << endl;
        cin >> userResponse;

        if (userResponse[0] == 'Y' || userResponse[0] == 'y') {
            cout << "The calculator lives on! " << endl;
            continue;
        } else if (userResponse[0] == 'N' || userResponse[0] == 'n') {
            cout << "The calculator will die now. For shame." << endl;
            break;
        } else {
            cout << "We're not sure what you want. Because of that, the calculator will die now." << endl;
            break;
        }
    }
    return 0;
}
