#include "allIncludes.h"

// Simple example on EARLY EXIT with different values.
// To be continued

int main()
{

	double u1, u2;

	// random seed
	//srand(time(NULL));

	u1 = (double (rand())) / ( double (RAND_MAX+1.0));
	cout << "RAND_MAX " << RAND_MAX << endl;
	cout << "u1=" << u1 << endl;

	u2 = (double (rand())) / ( double (RAND_MAX+1.0));
	cout << "RAND_MAX " << RAND_MAX << endl;
	cout << "u2=" << u2 << endl;

	if      ( u2 < 0.25){
		cout << "a. exit here?" << endl;
		return 1;
	}
	else if ( u2 < 0.50 ){
		cout << "b. exit here?" << endl;
		return 2;
	}
	else if ( u2 < 0.75){
		cout << "c. exit here?" << endl;
		return 3;
	}
	else{
		cout << "d. exit here?" << endl;
		return 4;
	}

	cout << "e. Am I ever here?" << endl;
	return 0;

}
