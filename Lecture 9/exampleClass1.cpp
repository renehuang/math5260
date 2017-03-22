#include "structures.h"
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

using namespace std;

// re: efficient handling of dynamic memory
// Dynamic memory through Constructor & Destructor

int main()
{

	int aSize1 = 20;  //10;
	int aSize2 = 30;  //20;
	int aSize3 = 40;  //30;
	int nRows = 1000000;
	int count1;

	struct timeval startTime, endTime; 
	long seconds, useconds; 
	double mtime;

	gettimeofday(&startTime, NULL);
	arraysClass arrays(aSize1, aSize2, aSize3);

	for (count1=1; count1<nRows; count1++){
		if ((count1%100000) == 0){
			cout << "count= " << count1 << endl;
		}
		builder1(arrays, aSize1, aSize2, aSize3);  
	}

	gettimeofday(&endTime, NULL); 
	seconds = endTime.tv_sec - startTime.tv_sec; 
	useconds = endTime.tv_usec - startTime.tv_usec; 
	mtime = ((seconds) * 1000.0 + useconds/1000.0); 
	cout << "Part 1 is done. Time elapsed was: " << mtime << " (milliseconds)" << endl;

	gettimeofday(&startTime, NULL);
	for (count1=1; count1<nRows; count1++){
		if ((count1%100000) == 0){
			cout << "count= " << count1 << endl;
		}
		builder2(aSize1, aSize2, aSize3);  
	}

	gettimeofday(&endTime, NULL); 
	seconds = endTime.tv_sec - startTime.tv_sec; 
	useconds = endTime.tv_usec - startTime.tv_usec; 
	mtime = ((seconds) * 1000.0 + useconds/1000.0); 
	cout << "Part 2 is done. Time elapsed was: " << mtime << " (milliseconds)" << endl;

}
