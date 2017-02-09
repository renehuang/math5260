#include "functions.h"
#include "lecture4_AllIncludes.h"

// bad example
//
void builder(int aSize1, int aSize2)
{
	int i1, i2;
	int **frequencies;

	for (int k1=0; k1< 10000; ++k1){
	
		cout << "allocation started " << k1 << " ..." << endl;
		frequencies = new int*[aSize1+1];
		for (i1=0; i1<=aSize1; i1++){
			frequencies[i1] = new int[aSize2+1];
		}
		cout << "allocation done" << endl;
		cout << " " << endl;

		cout << "before initialization" << endl;
		for (i1=0; i1<=aSize1; i1++){
			for(i2=0; i2<=aSize2; i2++){
				frequencies[i1][i2]= 1;
			}
		}
		cout << "after initialization" << endl;
		cout << " " << endl;

		cout << "deleting ..." << endl;
		for (i1=0; i1<=aSize1; i1++){
			delete [] frequencies[i1]; 
		}
		delete [] frequencies;
		cout << "deleting done" << endl;
	}
}

