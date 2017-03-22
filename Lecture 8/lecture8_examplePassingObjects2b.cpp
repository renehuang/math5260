#include <stdio.h> 
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <math.h>

using namespace std;


// using default Assignment Operator = for an object with dynamic memory

#ifndef _class_dynamic2DClass
#define _class_dynamic2DClass

class dynamic2DClass{

	int size1;
	int size2;

public:

	static int counter;

	int **twoDimPtr;
	dynamic2DClass(int size1, int size2);

	~dynamic2DClass();
};
#endif

int dynamic2DClass::counter = 0;

dynamic2DClass::dynamic2DClass(int sz1, int sz2){

	counter++;
	size1 = sz1;
	size2 = sz2;
	cout << "Inside Constructor: size1&size2 " << size1 << " " << size2 << endl;
	cout << "counter " << counter << endl;
	twoDimPtr = new int*[size1+1];
	for (int i=0; i<=size1; i++){
		twoDimPtr[i] = new int[size2+1];
	}

};

dynamic2DClass::~dynamic2DClass(){

	counter--;
	cout << "Inside Destructor: size1&size2 " << size1 << " " << size2 << endl;
	cout << "counter " << counter << endl;
	if (counter >=0){
		for (int i=0; i<=size1; i++){
			delete [] twoDimPtr[i];
		}
		delete [] twoDimPtr;
	}

};                                             

void builder1(dynamic2DClass & myArray, int size1, int size2)
{
	cout << "inside builder1" << endl;
	int i1, i2;
	for (i1=0; i1<=size1; i1++){
		for (i2=0; i2<=size2; i2++){
			myArray.twoDimPtr[i1][i2] = i1+i2; 
		}
	}

}

int main()
{
	int size1(2000);
	int size2(4000);
	dynamic2DClass myArray1(size1, size2);
	cout << " " << endl;

	cout << "calling builder ..." << endl;
	builder1(myArray1, size1, size2);

	cout << " declaring myArray2 & setting it equal to myArray1" << endl;
	dynamic2DClass myArray2 = myArray1;

	cout << " " << endl;
	cout << "exiting " << __FILE__ << endl;
	return 1;
}
