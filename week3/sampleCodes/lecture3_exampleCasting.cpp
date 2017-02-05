#include "allIncludes.h"

// simple example on Casting

int main()
{


	//int z1{0};
	
	int u1(0);
	int u2(0);

	double a1(0);
	double a2(0);

	cout << "a1(0) " << a1 << endl;

	a1 = 2.49;
	u1 = round(a1);
	cout << u1 << endl;

	cout << "a1 = 2.49 is " << a1 << endl;

	u1 = int (a1+0.5);
	cout << u1 << endl;

	a2 = 2.51;
	u2 = round(a2);
	cout << u2 << endl;

	u2 = int (a2+0.5);
	cout << u2 << endl;

	//a2(3.01);  // wrong

	int u3(0);
	//auto u4=u3;
	//cout << u4 << endl;

	int a3(3.14);
	//auto a4=a3;
	//cout << "a4=" << a4 << endl;

	return 1;

}
