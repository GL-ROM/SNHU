/* 5-1 Project two Gabriel Romero
*  Interest Calculator App
*/

#ifndef INTERESTCALCULATOR_H
#define INTERESTCALCULATOR_H

class InterestCalculator {

	// Declaring Public functions for definitions in InterestCalculator.cpp
	// Wanted to use getter and setter methods for practice
	public:
		void setInitialInvestment(double initialInvestment);		// Following set methods set the private variables 

		void setMonthlyDeposit(double monthlyDeposit);

		void setAnnualInterest(double annualInterest);

		void setNumberOfYears(int numberOfYears);

		double getInitialInvestment();								// Following get methods retreive the private variables and return them

		double getMonthlyDeposit();

		double getAnnualInterest();

		int getNumberOfYears();

		void yearEndReports(bool displayDeposits);					// Used to display year end balance reports bool was used as a condition

		void displayWelcomeMessage();								// Simple welcome message to display

		void displayFinancialData();								// Displays the first required splash screen with user inputs empty otherwise

		void displayMainMenu();										// Displays the choices after the data is displayed

		void setMenuChoice(int userSelection);						// Calls specific functions depending on the choice that was made

		void setFinancialData();									// Used to set all private values at once by calling the set methods

		void displayReport(bool display);							// Displays the beginning message for the reports and changes depending on the bool

		void returnToMainMenu();									// Returns the user to main menu after a short delay

		void inputValidation();										// Input validation for conituing into the app and returning to main menu
	
	// Declaring the private variables for this class
	private:
		double initialInvestment;
		double monthlyDeposit;
		double annualInterest;
		int numberOfYears;
		double closingBalance;

};

#endif