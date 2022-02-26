/* 5-1 Project two Gabriel Romero
*  Interest Calculator App
*/

// Declaring required libraries that will be used for the following methods
#include <iostream>
#include <ostream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <string>

// Declaring namespace for readablility and ease of use
using namespace std::this_thread;
using namespace std::chrono_literals;
using namespace std;

// Used to include our class header file 
#include "InterestCalculator.h"

// Following set methods simply set the private varible within the class object
void InterestCalculator::setInitialInvestment(double initialInvestment) {
	this->initialInvestment = initialInvestment;
};

void InterestCalculator::setMonthlyDeposit(double monthlyDeposit) {
	this->monthlyDeposit = monthlyDeposit;
};

void InterestCalculator::setAnnualInterest(double annualInterest) {
	this->annualInterest = annualInterest;
};

void InterestCalculator::setNumberOfYears(int numberOfYears) {
	this->numberOfYears = numberOfYears;
};

// Following get methods retrieve the private variables and return them when called
double InterestCalculator::getInitialInvestment() {
	return initialInvestment;
};

double InterestCalculator::getMonthlyDeposit() {
	return monthlyDeposit;
};

double InterestCalculator::getAnnualInterest() {
	return annualInterest;
};

int InterestCalculator::getNumberOfYears() {
	return numberOfYears;
};

// Displays the startup message for app and a brief explanation of the app
void InterestCalculator::displayWelcomeMessage() {
	cout << "\t* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *" << endl;
	cout << "\t* * * * * * * Welcome to Interest Calculator  * * * * * * *" << endl;
	cout << "\t* This application is intended to demonstrate the power   *" << endl;
	cout << "\t* of investments. Feel free to explore and change values. *" << endl;
	cout << "\t* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *" << endl;
	
	this->inputValidation();
};

// Displays the first required screen of the app. Displays the data if data was input if not it is left blank until data is entered.
void InterestCalculator::displayFinancialData() {
	cout << "\t* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *" << endl;
	cout << "\t* * * * * * * * * * Financial Data  * * * * * * * * * * * *" << endl;
	cout << "\t* Initial Investment Amount: $" << (this->getInitialInvestment() > 0 ? this->getInitialInvestment() : NULL) << endl;
	cout << "\t* Monthly Deposit: $" << (this->getMonthlyDeposit() > 0 ? this->getMonthlyDeposit() : NULL) << endl;
	cout << "\t* Annual Interset: " << (this->getAnnualInterest() > 0 ? this->getAnnualInterest() : NULL) << "%" << endl;
	cout << "\t* Number of years: " << (this->getNumberOfYears() > 0 ? this->getNumberOfYears() : NULL) << endl;
	cout << "\t* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *" << endl << endl;
	this->displayMainMenu();
};

// Displays the main menu with choices and calls menuChoice method with user input as argument
void InterestCalculator::displayMainMenu() {
	cout << "\t* * * * * * * * * * * * * * * * *" << endl;
	cout << "\t* * * * * Menu Options  * * * * *" << endl;
	cout << "\t* * * * * * * * * * * * * * * * *" << endl << endl;
	cout << "\t 1: Input new Financial Data" << endl << endl;
	cout << "\t 2: Show Balance and Interest Report Without Monthly Deposits" << endl << endl;
	cout << "\t 3: Show Balance and Interest Report With Monthly Deposits" << endl << endl;
	cout << "\t Please select an option and press the ENTER key: ";

	int userSelection;
	cin >> userSelection;

	this->setMenuChoice(userSelection);				// Call to menu choice which then calls the desired choice
};

// Uses the user input from main menu with a switch statement to decide which function to call based on choice
void InterestCalculator::setMenuChoice(int userSelection) {
	switch (userSelection) {
		case 1:
			this->setFinancialData();
			break;
		case 2:
			this->displayReport(false);				// Bool value is used here to discern between two different reports one with deposits and one without
			break;
		case 3:
			this->displayReport(true);
			break;
		default:									// Default case leaving it upen to add more options in the future
			cout << "Invalid choice. Please try again";
			this->displayMainMenu();				// Returns to display menu if bad choice was made
			break;
	}
};

// Sets all the private variables of the object in one place with statements
void InterestCalculator::setFinancialData() {
	system("cls");									// Using to clear screen when called. Will need alternative to this method but used for placeholder

	cout << "\tEnter Initial investment Amount: ";
	
	double tempDouble;								// Using a temp variable for user input to pass to all double methods
	cin >> tempDouble;

	this->setInitialInvestment(tempDouble);

	cout << endl;
	cout << "\tEnter Monthly Deposit: ";
	
	tempDouble = 0;
	cin >> tempDouble;

	this->setMonthlyDeposit(tempDouble);

	cout << endl;
	cout << "\tEnter Annual Interest: ";

	tempDouble = 0;
	cin >> tempDouble;

	this->setAnnualInterest(tempDouble);

	cout << endl;
	cout << "\tEnter Number of Years: ";

	int tempInt;
	cin >> tempInt;

	this->setNumberOfYears(tempInt);
	this->returnToMainMenu();						// Returns to main menu automatically after input is completed
}

// Displays the year end report frame. The data itself is populated by yearEndReports method depending on the true false condition
void InterestCalculator::displayReport(bool display) {
	system("cls");									// Using to clear screen when called. Will need alternative to this method but used for placeholder

	cout << (display ? "\t\tBalance and Interest With Additional Monthly Deposits" : "\t\tBalance and Interest Without Additional Monthly Deposits") << endl;
	cout << "\t=======================================================================================================" << endl;
	cout << setw(20) << right << "\t Year" << setw(40) << right << "Year End Balance" << setw(40) << right << "Year End Earned Interest" << endl;
	cout << "\t-------------------------------------------------------------------------------------------------------" << endl;

	this->yearEndReports(display);					// Fills table out with amount of years and year end balances

	cout << "\t-------------------------------------------------------------------------------------------------------" << endl << endl;

	this->inputValidation();						// Call to exit application or return to menu
}

// The main calculation function that presents the data within the end of year reports
void InterestCalculator::yearEndReports(bool displayDeposits) {
	double sumTotal = this->getInitialInvestment();
	double interest = (this->getAnnualInterest() / 100);
	double interestPerMonth = ((this->getAnnualInterest() / 100) / 12);

	if (displayDeposits) {															// Using if statments to determine which report to show based off true false
		for (int i = 1; i <= this->getNumberOfYears(); i++) {						// Iterates per year
			double totalInterest = 0;
			for (int j = 1; j <= 12; j++) {
				double interestAmount = (sumTotal + this->getMonthlyDeposit()) * interestPerMonth;		// iterates per month
				totalInterest = totalInterest + interestAmount;
				sumTotal = sumTotal + this->getMonthlyDeposit() + interestAmount;
			}
			ostringstream dollarSumTotal, dollarInterestTotal;						// Used to manipulate the double variable and add the dollar sign without
			dollarSumTotal << setprecision(2) << fixed << sumTotal;					// messing with the setw() and causing visual issues. Made it easir to concat
			dollarInterestTotal << setprecision(2) << fixed << totalInterest;

			string sumTotalString = dollarSumTotal.str();
			string interestTotalString = dollarInterestTotal.str();

			cout << fixed << setprecision(2) << setw(20) << i << setw(40) << "$" + sumTotalString << setw(40) << "$" + interestTotalString << endl << endl;
		}
	}
	else {
		for (int i = 1; i <= this->getNumberOfYears(); i++) {						// This loop shows the interest only without deposits
			double interestAmount = sumTotal * interest;
			sumTotal = sumTotal + interestAmount;

			ostringstream dollarSumTotal, dollarInterestTotal;						// Same deal as above, used for visual manipulation of data
			dollarSumTotal << setprecision(2) << fixed << sumTotal;
			dollarInterestTotal << setprecision(2) << fixed << interestAmount;

			string sumTotalString = dollarSumTotal.str();
			string interestTotalString = dollarInterestTotal.str();

			cout << fixed << setprecision(2) << setw(20) << i << setw(40) << "$" + sumTotalString << setw(40) << "$" + interestTotalString << endl << endl;
		}
	}
}

// Simple return to menu method with a small delay, for fun
void InterestCalculator::returnToMainMenu() {
	cout << endl << endl;

	cout << "\tReturning to main menu";
	for (int i = 0; i < 3; i++) {
		cout << ". ";
		sleep_for(1s);										// Small 1 second pause per loop
	}
	system("cls");

	this->displayFinancialData();
}

// Input validation with a pseudo valid check, any char outside of 1 will also return you to main menu 0 will exit application
void InterestCalculator::inputValidation() {
	string tempString;
	cout << "\tEnter 0 to EXIT or 1 to go to the MAIN MENU...";
	cin >> tempString;

	if (tempString == "0") {
		exit;
	}
	else {
		this->returnToMainMenu();
	}
}