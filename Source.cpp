#include <string>
#include <stdexcept>
#include <limits>

#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>

using namespace std;

// function Prototypes
void displayMultTable();
void doubleAValue();
void printMenu();


/*
Description:
   To call this function, pass the name of the Python function you wish to call and the string parameter you want to send
Example:
   int x = callIntFunc("doublevalue",5);
Return:
   Returned to the C++
*/
int callIntFunc(string proc, int param)
{
    char* procname = new char[proc.length() + 1];
    std::strcpy(procname, proc.c_str());

    PyObject* programName, * programModule, * programDiction, * programFunction, * pValue = nullptr, * presult = nullptr;
    // Initialize the Python Interpreter
    Py_Initialize();
    // Build the name object
    programName = PyUnicode_FromString((char*)"PythonCode");
    // Load the module object
    programModule = PyImport_Import(programName);
    // programDiction is a borrowed reference
    programDiction = PyModule_GetDict(programModule);
    // programFunction is also a borrowed reference
    programFunction = PyDict_GetItemString(programDiction, procname);
    if (PyCallable_Check(programFunction))
    {
        pValue = Py_BuildValue("(i)", param);
        PyErr_Print();
        presult = PyObject_CallObject(programFunction, pValue);
        PyErr_Print();
    }
    else
    {
        PyErr_Print();
    }
    //printf("Result is %d\n", _PyLong_AsInt(presult));
    Py_DECREF(pValue);
    // Clean up
    Py_DECREF(programModule);
    Py_DECREF(programName);
    // Finish the Python Interpreter
    Py_Finalize();

    // clean
    delete[] procname;

    return _PyLong_AsInt(presult);
}


void main()
{

    // create variable to hold user input
    int userInput;

    // begin a do-while loop as a menu to repeatedly ask user for input and control program flow.
    do {

        // print out instructions
        printMenu();

        try {

            // read user input into var
            cin >> userInput;

            // make sure the input is a valid, handled numberber, if not throw error and restart loop
            if (userInput > 3 || userInput < 1) {
                throw runtime_error("Invalid input numberber");
            }

            // use a switch statement to control program flow based on user input. Calls function corresponding to user choice
            // each function handles one choice
            switch (userInput) {
            case 1:
                displayMultTable();
                break;
            case 2:
                doubleAValue();
                break;
                // in the event the user chooses to exit (choice "3"), wave them goodbye. ("3" also exits enclosing while-loop)
            case 3:
                system("cls");
                cout << "Goodbye!" << endl;
                break;
            }
        }
        // catch any runtime errors. Print out error and restart while-loop
        catch (runtime_error& excpt) {
            system("cls");
            cout << excpt.what() << endl;
            cout << "Input must be 1, 2, or 3" << endl << endl;
            system("pause");
            system("cls");
        }

        // while the users choice is not 3, continue looping.
    } while (userInput != 3);
}

// function for printing program instructions
void printMenu() {
    cout << "1: Display a Multiplication Table" << endl;
    cout << "2: Double a Value" << endl;
    cout << "3: Exit" << endl;
    cout << endl;
    cout << "Enter your selection as a numberber 1, 2, or 3" << endl;
}

// C++ function for calling a python function which renders a multiplication table with input.
void displayMultTable() {

    // create a var to hold the value of the numberber the user wants to create a multiplication table for
    int userInput;

    // use a try-catch block to handle if a user enters a negative value
    try {
        system("cls");
        cout << "Enter a numberber for the multiplication table" << endl;
        cin >> userInput;

        // throw a runtime_error if user input is negative
        if (userInput < 0) {
            throw runtime_error("No negative number allowed");
        }

        // call the callIntFunc which calls a method in python and passes the userInput value to said method.
        callIntFunc("MultiplicationTable", userInput);

        cout << endl;

        // clear screen and exit
        system("pause");
        system("cls");

    }
    // if the user entered negative input, makes them aware and exits back to start of program
    catch (runtime_error& excpt) {
        system("cls");
        cout << excpt.what() << endl;
        cout << "Entered a negative number" << endl;
        cout << endl;
        system("pause");
        system("cls");
    }
}

// C++ function for calling a python function that returns a double value
// DISCLAIMER: All commentary in doubleAValue() is the same as in MultiplicationTable function, up to the Int Function. Skip ahead to see below:
void doubleAValue() {

    int userInput;

    try {
        system("cls");
        cout << "Enter a number to double" << endl;
        cin >> userInput;

        if (userInput < 0) {
            throw runtime_error("No negative number allowed here :");
        }

        system("cls");

        // Here, we call the In Function again, but this time we specify a different function to call in the Python module
        // and once again pass this function userInput.
        cout << callIntFunc("DoubleValue", userInput) << endl;

        system("pause");
        system("cls");

    }
    catch (runtime_error& excpt) {
        system("cls");
        cout << excpt.what() << endl;
        cout << "Entered a negative number: " << endl;
        cout << endl;
        system("pause");
        system("cls");

    }

}
