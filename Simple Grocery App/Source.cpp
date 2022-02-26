#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <algorithm>
#include <fstream>
#include <iomanip>


using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
	
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

// Function Prototyping

void callMainMenu();
void userMenuSelection(int userSelection);
void returnToMainMenu();
int specificItemSearch();
void histogramOfItems();


void main()
{
	callMainMenu();
}


// Function Definitions

// Displays the main manu and calls user selection functions with user input
void callMainMenu() {
	int userInput;
	cout << "--------------- Main Menu --------------- " << endl << endl;
	cout << "[1] Display Frequency of Items Purchased Today." << endl;
	cout << "[2] Display Frequency of Specific Items Purchased Today. (Enter Item Name)" << endl;
	cout << "[3] Display Histogram of Items purchased from File." << endl;
	cout << "[4] Exit" << endl << endl;
	cout << "Selection: ";

	cin >> userInput;
	userMenuSelection(userInput);

}

// Decides which functions to call depending on the input passed to the function
void userMenuSelection(int userSelection) {
	cout << endl;
	switch (userSelection) {
	case 1:
		CallProcedure("printAllItemsCount");
		returnToMainMenu();								// loops back to the main menu
		break;											// Redundant breaks to avoid any loops
	case 2:
		cout << specificItemSearch() << " is the count." << endl << endl;		// Simple display of number even though python prints a simple table format of it. Added for prompt in project readme.
		returnToMainMenu();
		break;
	case 3:
		histogramOfItems();								// Calls histogram function
		returnToMainMenu();
		break;
	case 4:
		cout << "Thank you for using this application. Exiting." << endl;
		return;
		break;
	default:
		cout << "Input a valid selection (1, 2, 3 or 4)." << endl;
		returnToMainMenu();
		break;
	}
}

void returnToMainMenu() {
	//system("CLS");
	cin.clear();										// Clears cin buffer
	cin.ignore(10000, '\n');							// Ignores new line characters to prevent loop

	callMainMenu();
}

// Asks user for input and passes value to python function to find item within list and return its count
int specificItemSearch() {
	string userItem;

	cout << "Enter the name of the item you wish to know the frequency of." << endl;
	cout << "Item name: ";
	
	cin >> userItem;										
	for_each(userItem.begin(), userItem.end(), [](char& c) {		// Used to set entire string to lower case for validation
		c = tolower(c);
	});

	userItem[0] = toupper(userItem[0]);								// Upcases the first letter in the string for validation

	cout << endl;													// For spacing in terminal

	int itemValue = callIntFunc("printSpecificItemCount", userItem);	// Sets variable to return but still calls function for nicer printout

	if (itemValue < 0) {
		cin.clear();									// Clears cin buffer
		cin.ignore(10000, '\n');						// Ignores new line characters to prevent loop

		specificItemSearch();
	}
	else {
		return itemValue;
	}
}

// Reads python created file frequency.dat and generates histogram based off that file per entry and value
void histogramOfItems() {
	CallProcedure("creatDataFile");						// Calls the python function to generate the file info
	ifstream dataFile ("frequency.dat");				// Opens the file for reading purposes
	string itemName, itemQuantity;						// Declared first variables to grab first two instances of data from file
	string greenFont = "\033[32;1m";					// Messing with colors in console
	string whiteFont= "\033[0m";

	dataFile >> itemName;								// Grabs first item name
	dataFile >> itemQuantity;							// Grabs first item quantity

	cout << setw(15) << "------ Item Histogram One Count Denoted By " << greenFont << "[]" << whiteFont << " ------" << endl;

	if (dataFile.is_open()) {							// checks to ensure file is open
		while (dataFile) {
			cout << whiteFont << setw(15) << itemName << ": ";
			for (int i = 0; i < stoi(itemQuantity); i++) {		// Loop to generate historgram graphic
				cout << greenFont << "[]";
			}
			cout << endl;
			dataFile >> itemName;
			dataFile >> itemQuantity;
		}
	}
	else {
		cout << "ERROR File was not open" << endl;		// If for some reason file was not open error out
	}

	dataFile.close();
	cout << whiteFont << endl;							// resets font color for app
}
