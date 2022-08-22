#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>

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
// Function that initiates and iterates the program
void MenuIntricacies() {
	int userInput;
	bool continueProgram = true;

	// Iterates Menu displlay 
	do {
		cout << "---------------------------- User Menu ----------------------------" << endl;
		cout << "1: Produce a list of all items purchased with frequency of purchase" << endl;
		cout << "2: Display how many times a specific item was sold" << endl;
		cout << "3: Produce a text histogram of sales data" << endl;
		cout << "4: Exit \n" << endl;
		cout << "Enter your choice as a number: 1, 2, 3, or 4." << endl;
		cout << "-------------------------------------------------------------------" << endl;

		// Prepares to throw exception
		try {
			cin >> userInput;
			cout << endl;

			if ((userInput < 1) || (userInput > 4)) {
				throw (userInput);
			}
		}
		// Catches exception whenever there is an error with userInput, resets loop
		catch (...) {
			cout << "Invalid Input. Please Enter: 1, 2, 3, or 4.\n" << endl;
		}

		// Choice 1 Displays all items bought with quantity
		if (userInput == 1)
		{
			cout << endl;
			cout << "********************************************************************************" << endl;
			cout << "-------------------	Total Produce Purchased Today	-------------------------" << endl;
			cout << "********************************************************************************" << endl;
			cout << endl;
			// Calls python function to read the file
			CallProcedure("read_File");
		}

		// Choice 2 prompts user to enter string for product name
		// It displays the product name and quantity sold for that product only
		else if (userInput == 2) {
			string userString;
			cout << "Please Enter The Product You Wish To Look Up: ";
			cin >> userString;	// Product name input from user
			cout << endl;
			/* change tot to productCount */
			int productCount = callIntFunc("locate_Total_Product_Amount", userString); // Calls python funciton that reads the frequency of the string in the file
			if (productCount == -1) {
				cout << "This item is not in the list." << endl;
			}
			else {
				cout << endl << "A total of " << productCount << " " << userString << " was sold today." << endl << endl;
			}
		}
		else if (userInput == 3) {
			// Calls python function that displays the histogram for the quantity of each sold item
			CallProcedure("read_And_Write_File");
		}
		else if (userInput == 4) {
			// Ends the do loop
			continueProgram = false;
		}
		else {
			cout << "\nPlease Try Again" << endl;
		}

	} while (continueProgram == true);

}

// Main Code
int main()
{

	MenuIntricacies();

	cout << "You've exited the program" << endl;

	return 0;
}