/* Gabriel Romero
*  4-4 Assignment File Input Output Fahrenheit to Celcius
*/


#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

vector<int> FahrenheitToCelcius(vector<int> temperatureVector) {
	for (int i = 0; i < temperatureVector.size(); i++) {
		temperatureVector.at(i) = ((temperatureVector.at(i) - 32) * (5.0 / 9.0));
	}

	return temperatureVector;
}

int main() {
	ifstream inFS;
	string location;
	int temperature;
	vector<string> locations;
	vector<int> temperatures;

	// Open the file
	cout << "Opening file FahrenheitTemperature.txt..." << endl;
	inFS.open("FahrenheitTemperature.txt");

	// Error checking if file cannot open
	if (!inFS.is_open()) {
		cout << "Could not open FarenheitTemperature.txt." << endl;
		return 1;
	}

	// Inital Grab of data before loop
	inFS >> location;
	inFS >> temperature;

	// Read in data to vectors
	while (!inFS.fail()) {
		locations.push_back(location);						// Adds the location to locations vector
		temperatures.push_back(temperature);				// Adds the temperatures to temperatures vector
		inFS >> location;
		inFS >> temperature;
	}

	// Error checking if end of file not reached
	if (!inFS.fail()) {
		cout << "Could not reach end of file, an error occured." << endl;
	}

	cout << "Now closing the file..." << endl;

	// Closing file
	inFS.close();

	ofstream outFS;			// Output file stream

	outFS.open("CelsiusTemperature.txt");

	// Error checking if file cannot open
	if (!outFS.is_open()) {
		cout << "Could not open file CelsiusTemperature.txt" << endl;
		return 1;
	}

	vector<int> celsiusTemps = FahrenheitToCelcius(temperatures);		// Creating a vector of celsius temps by calling function

	// Loop to write into file the location and temperature in Celsius
	for (int i = 0; i < celsiusTemps.size(); i++) {
		outFS << locations.at(i) << " " << celsiusTemps.at(i) << " C" << endl;
	}

	// Finished with file and closes
	outFS.close();

}
