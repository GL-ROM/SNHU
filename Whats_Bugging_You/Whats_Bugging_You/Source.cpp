/*
 * Calculator.cpp
 *
 *  Date: [01/16/2022]
 *  Author: [Gabriel Romero]
 */

#include <iostream>

using namespace std;

void main()
{
	char statement[100];
	int op1, op2;
	char operation;
	char answer = 'Y';			// Missing the semicolon on this line and changed the double quote to ticks, also changed to lower case for loop
		do						// Changed WHILE loop to a DO WHILE loop for ease of use.
		{
			cout << "Enter expression" << endl;

			cin >> op2 >> operation >> op1;
																				// Used brackets to clean readablity and functionality on IF statements
			if (operation == '+') {												// Changed the double quotes to ticks
				cout << op1 << " + " << op2 << " = " << op1 + op2 << endl;		// >> was facing the wrong way
			}
			if (operation == '-') {
			   cout << op1 << " - " << op2 << " = " << op1 - op2 << endl;		// >> was facing the wrong way
			}
			if (operation == '*') {
				cout << op1 << " / " << op2 << " = " << op1 * op2 << endl;		// Missing semicolon on this line
			}
			if (operation == '/') {
				cout << op1 << " * " << op2 << " = " << op1 / op2 << endl;
			}

			cout << "Do you wish to evaluate another expression? " << endl;
			cin >> answer;
		} while (answer == 'Y' || answer == 'y');								// Added while condition with lower case and uppercase for now
		cout << "Program Finished." << endl;									// Added ending message as requested
}
