#include "allIncludes.h"

#include "functions.h"

// passing by reference
void multFunc2(const double & factor, double & width, double & height)
{

	width  = factor*width;
	height = factor*height;

	cout << "inside multFunc2: " << width << " " << height << endl;

	//factor  = 4.0; // Cannot do, declared constant
}
