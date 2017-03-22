#include <stdio.h> 
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <math.h>

using namespace std;

// Copy Constructor

#ifndef _class_dummyClass
#define _class_dummyClass

class dummyClass{

public:

	int size1;
	int size2;
	
	dummyClass(){
		cout << "Inside default Constructor" << endl;
		size1 = 10;
		size2 = 20;
	}

	dummyClass(int x1, int x2){
		cout << "Inside Constructor" << endl;
		size1 = x1;
		size2 = x2;
	}
	
	//Copy Constructor
	dummyClass (const dummyClass & myArray)
	{
		cout << "Inside Copy Constructor" << endl;
		size1 = myArray.size1;
		size2 = myArray.size2;
	}

	~dummyClass(){
		cout << "Inside Destructor" << endl;
	}
};
#endif    

void builder1(dummyClass &myArray)
{
	cout << "inside builder1" << endl;

	cout << "size1&size2 " << myArray.size1  << " " << myArray.size2 << endl;

}

int main()
{
	
	cout << " " << endl;
	dummyClass myArray0;
	
	cout << " " << endl;
	int size1(20);
	int size2(40);
	dummyClass myArray1(size1, size2);

	cout << " " << endl;
	cout << "setting myArray2 equal to myArray1" << endl;
	dummyClass myArray2; // = myArray1;

	myArray2 = myArray1;

	cout << " " << endl;
	cout << "calling Builder1 " << endl;
	builder1(myArray2);
	cout << "Builder1 called" << endl;

	cout << " " << endl;
	cout << "exiting " << __FILE__ << endl;


	cout << " " << endl;
	return 1;

}
