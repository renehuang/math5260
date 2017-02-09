#include "lecture4_AllIncludes.h"

// First Example on pointers & dynmaic allocation
// simple example of various dynamic allocation
// pros & cons

int main(){

	struct timeval startTime, endTime; 
	long seconds, useconds; 
	double mtime;

	int i1, i2, i3, i4;
	int j1;
	int nIters = 1000;

	int aSize1 = 100;
	int aSize2 = 200;
	int aSize3 = 10;
	int aSize4 = 20;
	
	double *myPtr2;
	myPtr2 = new double [(aSize1+1)*(aSize2+1)*(aSize3+1)*(aSize4+1)];
	
	gettimeofday(&startTime, NULL); 

	for (j1=0; j1<nIters; j1++){
		
		for (i1 = 0; i1<=aSize1; ++i1){
			for (i2 = 0; i2<=aSize2; ++i2){
				for (i3 = 0; i3<=aSize3; ++i3){
					for (i4 = 0; i4<=aSize4; ++i4){
						myPtr2[i4*aSize1*aSize2*aSize3 + i3*aSize1*aSize2 + i2*aSize1 + i1] = 1.0;
					}
				}
			}
		}
	}
	
	gettimeofday(&endTime, NULL); 
	seconds = endTime.tv_sec - startTime.tv_sec; 
	useconds = endTime.tv_usec - startTime.tv_usec; 
	mtime = ((seconds) * 1000 + useconds/1000.0); 
	cout << "single-dimensional case is done. Time elapsed was: " << mtime << " (milliseconds)" << endl;
				

	delete [] myPtr2;

	double ****myPtr1;
	myPtr1 = new double***[aSize1+1];
	for (i1=0; i1<=aSize1; i1++){
		myPtr1[i1] = new double**[aSize2+1];
		for (i2=0; i2<=aSize2; i2++){
			myPtr1[i1][i2] = new double*[aSize3+1];
			for (i3=0; i3<=aSize3; i3++){
				myPtr1[i1][i2][i3] = new double[aSize4+1];
			}
		}
	}
	
	gettimeofday(&startTime, NULL); 

	// direct access
	for (j1=0; j1<nIters; j1++){
		for (i1 = 0; i1<=aSize1; ++i1){
			for (i2 = 0; i2<=aSize2; ++i2){
				for (i3 = 0; i3<=aSize3; ++i3){
					for (i4 = 0; i4<=aSize4; ++i4){
						myPtr1[i1][i2][i3][i4] = 1.0;
					}
				}
			}
		}
	}

	gettimeofday(&endTime, NULL); 
	seconds = endTime.tv_sec - startTime.tv_sec; 
	useconds = endTime.tv_usec - startTime.tv_usec; 
	mtime = ((seconds) * 1000 + useconds/1000.0); 
	cout << "multi-dimensional case is done. Time elapsed was: " << mtime << " (milliseconds)" << endl;

	for (i1=0; i1<=aSize1; i1++){
		for (i2=0; i2<=aSize2; i2++){
			for (i3=0; i3<=aSize3; i3++){
				delete [] myPtr1[i1][i2][i3];
			}
			delete [] myPtr1[i1][i2];
		}
		delete [] myPtr1[i1];
	}
	delete [] myPtr1;


	return 0;
}
