#include "lecture4_AllIncludes.h"

// Simple example on Arrays.
// Segmentation Fault (core dumped)
// To be continued

int main()
{
	int i1;

	// one-dimensional arrays
	int nSize = 10;
	int dummy0[  ] = {0,1,2,3,4,5,6,7,8,9};
	int dummy1[10] = {0,1,2,3,4,5,6,7,8,9};
	int dummy2[10] = {0,1,2};
	int dummy3[10] = {};

	int sum1 = 0;
	for (i1=0; i1<10; ++i1){
		cout << " dummy0[" << i1 << "]=" << dummy0[i1];
		cout << " dummy1[" << i1 << "]=" << dummy1[i1];
		cout << " dummy2[" << i1 << "]=" << dummy2[i1];
		cout << " dummy3[" << i1 << "]=" << dummy3[i1] << endl;
		sum1 += dummy0[i1];
	}
	cout << "sum1 = " << sum1 << endl;

	int i2 = 5;
	int dummy4[10];
	dummy4[3] = 79;
	dummy4[0] = -5;
	dummy4[i2] = 86;
	dummy4[i2+2] = dummy4[i2] - 30;
	dummy4[15] = 10;


	for (i1=0; i1<10; ++i1){
		cout << "dummy4[" << i1 << "]=" << dummy4[i1] << endl;
	}

	cout << "duumy[15]=" <<dummy4[15] << endl; // exceeding the dimnesion
	cout << "dummy[17]=" << dummy4[17] << endl; // exceeding the dimnesion

	// multi-dimensional arrays

	cout << " 2-D Matrix " << endl;
	int stiffnessMatrix[40][30];
	cout << stiffnessMatrix[4][6] << endl;
	stiffnessMatrix[5][4] = 4;
	
	cout << " 3-D Matrix " << endl;
	int matrixD[10][30][20];
	cout << matrixD[0][0][0] << endl;
	//cout << matrixD[11][31][21] << endl;
	// Segmentation fault (core dumped)
	cout << matrixD[15][30][20] << endl;
	
	cout << " I am here" << endl;
	return 0;

}