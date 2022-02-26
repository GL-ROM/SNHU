/* 12 and 24 Hour Clock
*  Project 3-1 (1)
*  Author: Gabriel Romero
*/

#pragma warning(disable : 4996) // Used to avoid deprecation issues
#include<iostream>
#include<ctime>
#include<iomanip>

using namespace std;

// Clock class containing methods to edit and display the clock
class Clock {
private:
	struct tm* localTime;
	int clockHours = 0;						// Initializes variables for clock time
	int clockMinutes = 0;
	int clockSeconds = 0;
	bool clock24HourFormat;

public:
	Clock(bool clock24HourFormat) {			// To set the type of clock true being 24 false being 12
		this->clock24HourFormat = clock24HourFormat;
	}

	void addHour() {			// Adds one hour to the current clock time
		clockHours += 1;
	}

	void addMinute() {			// Adds one minute to the current clock time
		clockMinutes += 1;
	}

	void addSecond() {			// Adds one second to the current clock time
		clockSeconds += 1;
	}

	// Switch statement to invoke the function selected by the user
	void userChoice(Clock &clock, int choice, bool &exit) {		// Takes in the object that is set to change and calls on itself passing exit variable and user choice
		switch (choice) {
			case 1:
				this->addHour();
				break;
			case 2:
				this->addMinute();
				break;
			case 3: 
				this->addSecond();
				break;
			case 4:
				exit = true;
			default:
				break;
		}
	}

	// Display function that displays the corrected time in each respective location
	void displayClock(ostream& out) {
		int hours = 0;
		int minutes = 0;
		int seconds = 0;
		time_t secs = time(0);				// Grabbing the total seconds
		localTime = localtime(&secs);

		seconds = localTime->tm_sec + clockSeconds;		// Calculations to compute current time based on the secs variable
		minutes += (seconds / 60);
		seconds = (seconds % 60);

		minutes += localTime->tm_min + clockMinutes;
		hours += (minutes / 60);
		minutes = (minutes % 60);

		hours = (hours + localTime->tm_hour + clockHours);

		bool noon;							// Used to decipher if noon or not to correctly display 12
		((hours % 12 == 0) ? noon = true : noon = false);

		out << setw(2) << setfill('0') << (clock24HourFormat ? hours : (noon ? 12 : (hours % 12))) << ":";
		out << setw(2) << setfill('0') << minutes << ":";
		out << setw(2) << setfill('0') << seconds << " ";
		if (!clock24HourFormat) {			// Display PM or AM
			if (hours >= 12) {
				out << "PM";
			}
			else {
				out << "AM";
			}
		}

		// To FIX need number of hours goes beyond 24 hours and does not cycle around. The functions that were asked for are working as intended though. 
	}
};

// Displays the menu options for user
void showMenu() {
	cout << "\t*************************" << endl;
	cout << "\t** 1 - Add One Hour    **" << endl;
	cout << "\t** 2 - Add One Minute  **" << endl;
	cout << "\t** 3 - Add One Second  **" << endl;
	cout << "\t** 4 - Exit            **" << endl;
	cout << "\t*************************" << endl;
}

// Displays the clock information at the top, passes two objects
void showClocks(Clock clock1, Clock clock2) {
	cout << "*******************     *******************" << endl;
	cout << "*  12 Hour Clock  *     *  24 Hour Clock  *" << endl;
	cout << "*   " << setw(15);
	clock1.displayClock(cout);
	cout << "   *     ";
	cout << "*   " << setw(15);
	clock2.displayClock(cout);
	cout << "     *" << endl;
	cout << "*******************     *******************" << endl << endl;
}

int main() {
	Clock clock12(false), clock24(true);
	int userInput;
	bool exit = false;

	while (!exit) {						// Simnple while loop to continue while the variable is false
		
		showClocks(clock12, clock24);

		showMenu();

		cin >> userInput;

		clock12.userChoice(clock12, userInput, exit);
		clock24.userChoice(clock24, userInput, exit);

		system("CLS");
	}

}