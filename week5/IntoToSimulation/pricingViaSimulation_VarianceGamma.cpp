#include "functions.h"

#include <iostream>
#include <iomanip>
#include <ios>
#include <math.h>  /* log & exp */
#include <stdio.h>
#include <sys/time.h> 
#include <cstdlib>

using namespace std;

int main(int argc, char*argv[])
{

	long idum = atol(argv[1]);

	double   sigma=0.20, nu=0.40, theta=-0.3;

	double   maturity = 0.25;
	double   s0 = 200.0;
	double   strike = 170.0;
	double   rfr=0.0075, div=0.0175;

	int nSimulationPaths = 4000000;
	int nTimeSteps = 40;

	double dt = maturity/nTimeSteps;

	double drift = (rfr-div)*dt + (dt/nu)*log(1.0-theta*nu-sigma*sigma*nu/2.0);
	double payoff1 = 0.0;
	double price1, call1;

	int iI, jJ;
	double g1, u1, z1;
	double fd1, feed1;


	for (jJ = 0; jJ<nSimulationPaths; jJ++){

		fd1 = log(s0);

		for (iI = 0; iI<nTimeSteps; iI++){

			g1 = gamrand(dt/nu, nu, &idum);
			
			//u1 = (double)rand() / ((double)RAND_MAX+1.0);
			u1 = ran2_mod(&idum);
			z1 = invNormal(u1);
			feed1 = theta*g1 + sigma*sqrt(g1)*z1;
			fd1 = fd1+feed1+drift;
			price1 = exp(fd1);

		}
		if (price1 > strike){
			payoff1 = payoff1 + (price1-strike);
		}
	}

	call1 = exp(-rfr*maturity)*payoff1/nSimulationPaths;
	cout << "European Call premium: " << call1 << endl;

}
