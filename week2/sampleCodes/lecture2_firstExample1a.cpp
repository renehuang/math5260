//#include "functions.h"
#include <iostream>
//#include <stdio.h>

// g++ -o *.out *.cpp

// ===================
// Very First Example 
// ===================

// OR

/* =================
 Very First Example 
====================*/

int main()
{

	int i1;
	int i2;
	int result;

	// Default values for i1 & i2
	std::cout << "i1=" << i1 << std::endl;
	std::cout << "i2=" << i2 << std::endl;
	

	std::cout << "Enter a number: ";
	std::cin >> i1;
	std::cout << " for i1 you entered: " << i1 << std::endl;

	std::cout << "Enter another number: ";
	std::cin >> i2;
	std::cout << " for i2, your entered: " << i2 << std::endl;

	result = i1+i2;

	std::cout << i1 << "+" << i2 << "=" << result << std::endl;

	return 1;

}
