//#include "functions.h"

#include <iostream>

using namespace std;

// ===================
// Very First Example 
// ===================

// OR

/* =================
 Very First Example 
====================*/

int main()
{

	double i1, i2;
	double result;

	// Default values for i1 & i2
	cout << "i1=" << i1 << endl;
	cout << "i2=" << i2 << endl;

	cout << "Enter a number: ";
	cin >> i1;
	cout << " for i1 you entered: " << i1 << endl;

	cout << "Enter another number: ";
	cin >> i2;
	cout << " for i2, your entered: " << i2 << endl;

	result = i1+i2;

	cout << i1 << "+" << i2 << "=" << result << endl;

	return 1;

}
