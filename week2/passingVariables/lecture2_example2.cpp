#include "functions.h"

#include <sys/time.h> 
#include <stdio.h> 
#include <unistd.h> 
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdlib.h>
#include <math.h>
#include <time.h>

//using namespace std;

int main()
{

	struct timeval startTime, endTime; 
	long seconds, useconds; 
	double mtime;


	int i1;
	int nIter(1000000);
	cout << "nIter: " << nIter << endl;

	string myString1 = "MATHG5260 is a C++ programming course for Master Program (Spring 2017) at Columnbia University";
	string myString2 = " This course covers features of the C++ programming language which are essential in Quant/Comp Finance and its applications. We start by covering basic C++ programming features and then move to some more advance features. We utilize these features for financial engineering and quantitative finance applications";
	string myString3, myString4;
	
	gettimeofday(&startTime, NULL); 
	for (i1=0; i1<nIter; i1++){
		myString3 = concatFunc1(myString1, myString2);
	}
	gettimeofday(&endTime, NULL); 
	seconds = endTime.tv_sec - startTime.tv_sec; 
	useconds = endTime.tv_usec - startTime.tv_usec; 
	mtime = seconds*1000 + useconds/1000.0; 
	cout << "concatenation of two strings by value is done. Time elapsed was: " << mtime << " (milliseconds)" << endl;

	
	
	gettimeofday(&startTime, NULL); 
	for (i1=0; i1<nIter; i1++){
		myString4 = concatFunc2(myString1, myString2);
	}
	gettimeofday(&endTime, NULL); 
	seconds = endTime.tv_sec - startTime.tv_sec; 
	useconds = endTime.tv_usec - startTime.tv_usec; 
	mtime = seconds*1000 + useconds/1000.0; 
	cout << "concatenation of two strings by reference is done. Time elapsed was: " << mtime << " (milliseconds)" << endl;



	return 1;

}
