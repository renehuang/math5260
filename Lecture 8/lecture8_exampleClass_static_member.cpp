#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>

using namespace std;

// Class Example with static member

class arraysClass {
public:

	double *myArray;

	arraysClass(int arraySize){
		myArray = new double [arraySize];
		cout << " " << endl;
		cout << "constructor: out of arraysClass constructor successfully" << endl;
		usleep(2000000);
	};

	~arraysClass(){
		delete [] myArray;
		cout << " " << endl;
		cout << "destructor: out of arraysClass destructor successfully" << endl;
		usleep(2000000);
	};

};


class CountObj {

public:

	static int nCounts;

	CountObj(){
		nCounts++;
		cout << "inside constructor of CountObj: " << nCounts << endl;
		usleep(1000000);
	};

	~CountObj(){
		nCounts--;
		cout << "inside destructor of CountObj: " << nCounts << endl;
		usleep(1000000);
	};
};

int CountObj::nCounts=0;



int main() 
{

	/* ----------------------
	constructor & destructor
	-----------------------*/

	int arraySize = 100;
	cout << " " << endl;
	cout << "calling arraysClass ... " << endl;
	arraysClass arrays(arraySize);
	cout << "arraysClass called!" << endl;

	cout << " " << endl;
	cout << "dynamic allocation of size 5 started ..." << endl;
	CountObj *countPtr1 = new CountObj [5];
	cout << "dynamic allocation  ended." << endl;

	cout << " " << endl;
	cout << "dynamic allocation of size 8 started ..." << endl;
	CountObj *countPtr2 = new CountObj [8];
	cout << "dynamic allocation ended." << endl;

	cout << " " << endl;
	cout << "static array of size 10 started ..." << endl;
	CountObj dummy[10];
	cout << "static array ended ..." << endl;

	cout << " " <<endl;
	cout << "just an object started" << endl;
	CountObj temp;
	cout << "ended " << endl;

	cout << " " << endl;
	cout << "temp.nCounts:" << temp.nCounts << endl;
	cout << "CountObj::nCounts " << CountObj::nCounts << endl;

	cout << " " << endl;
	cout << "deleting countPtr1 ... " << endl;
	delete [] countPtr1;
	cout << "deleted" << endl;

	cout << "temp.nCounts:" << temp.nCounts << endl;
	cout << "CountObj::nCounts " << CountObj::nCounts << endl;

	cout << " " << endl;
	cout << "deleting countPtr2 ..." << endl;
	delete [] countPtr2;
	cout << "deleted ... " << endl;

	cout << "temp.nCounts:" << temp.nCounts << endl;
	cout << "CountObj::nCounts " << CountObj::nCounts << endl;

	cout << " " << endl;
	cout << "End of the program" << endl;
	return 0;
}
