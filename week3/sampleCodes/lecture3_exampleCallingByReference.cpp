
#include "allIncludes.h"
#include "functions.h"

// One more example
// very simple example on calling by value & reference

int main()
{

	double width(0);
	double height(0);

	double factor = 2.5;

	width = 2.5;
	height = 3.5;

	cout << " " << endl;
	cout << "width=" << width << " height=" << height << endl;

	cout << " " << endl;
	cout << "---------------------------------------" << endl;
	multFunc1(factor, width, height);
	cout << "after multFunc1: width=" << width << " height=" << height << endl;

	cout << " " << endl;
	cout << "---------------------------------------" << endl;
	multFunc2(factor, width, height);
	cout << "after multFunc2: width=" << width << " height=" << height << endl;


	return 1;

}
