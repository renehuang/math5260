#include "allIncludes.h"

#include "functions.h"

// Passing by value
void multFunc1(const double & factor, double width, double height)
{
	width  = factor*width;
	height = factor*height;
	
	cout << "inside multFunc1: " << width << " " << height << endl;
}
