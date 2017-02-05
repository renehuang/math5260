#include "allIncludes.h"

#include "functions.h"

// simple example on writing the output into a BINARY file vs. an ASCII file

//-------------------------------
// Comparing ASCII vs BINARY
//--------------------------------

int main(int argc, char*argv[])
{
	int i1;
	int nRows = 20000000;
	double i2, dummy;


	// time measurement in milliseconds
	struct timeval startTime, endTime; 
	long seconds, useconds; 
	double mtime;

	//==========================
	//      BINARY FORMAT 
	//==========================

	gettimeofday(&startTime, NULL); 


	string output1 = "output1.bin"; 
	ofstream output1File; 
	remove(output1.c_str()); // removing any file with the same name
	output1File.open(output1.c_str(), ios::out | ios::binary | ios::app);
	//ios::out	Open for output operations, allows output (write operations) to a stream.
    	//ios::binary	Open in binary mode.
    	//ios::app	All output operations are performed at the end of the file (i.e. appending)
    	// | (bitwise OR operator)
	// Is ios:: app necessary?


	// some non-sense operations
	for (i1=1; i1<=nRows; i1++){
		i2 = double (i1);
		dummy = rem(i2, 10.0);
		output1File.write(reinterpret_cast<const char *> (&dummy), sizeof(double));
	}
	output1File.close();


	gettimeofday(&endTime, NULL); 
	seconds = endTime.tv_sec - startTime.tv_sec; 
	useconds = endTime.tv_usec - startTime.tv_usec; 
	mtime = ((seconds) * 1000.0 + useconds/1000.0); 

	cout << "Writing into BINARY output is done. Time elapsed was: " << mtime << " (milliseconds)" << endl;
	//------------------------------------------------------------------------------------------------------


	//=========================
	//       ASCII FORMAT
	//=========================
	gettimeofday(&startTime, NULL); 


	FILE *output2;
    	output2 = fopen("output1.dat", "w");

	// some non-sense operations
	for (i1=1; i1<=nRows; i1++){
		i2 =  double (i1);
		dummy = rem(i2, 10.0);
		fprintf(output2, "%lf \n", dummy);
	}
    	fclose(output2);

	gettimeofday(&endTime, NULL); 
	seconds = endTime.tv_sec - startTime.tv_sec; 
	useconds = endTime.tv_usec - startTime.tv_usec; 
	mtime = ((seconds) * 1000 + useconds/1000.0); 


	cout << "Writing into ASCII output is done. Time elapsed was: " << mtime << " (milliseconds)" << endl;
	//----------------------------------------------------------------------------------------------------


	return 0;
}


