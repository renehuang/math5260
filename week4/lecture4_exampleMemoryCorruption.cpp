#include "functions.h"

#include "lecture4_AllIncludes.h"

// Example on memory corruption

int main()
{

	int aSize1 = 10000;
	int aSize2 = 50000;

	struct timeval startTime, endTime; 
	long seconds, useconds; 
	double mtime;

	gettimeofday(&startTime, NULL);

	builder(aSize1, aSize2); 

	gettimeofday(&endTime, NULL); 
	seconds = endTime.tv_sec - startTime.tv_sec; 
	useconds = endTime.tv_usec - startTime.tv_usec; 
	mtime = ((seconds) * 1000.0 + useconds/1000.0); 
	cout << "Run is done. Time elapsed was: " << mtime << " (milliseconds)" << endl;

	return 0;

}

